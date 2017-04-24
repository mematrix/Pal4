// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <random>
#include <thread>

#include "FCharacterRoundDispatcher.h"

std::default_random_engine generator;
std::uniform_int_distribution<int32> distribution(FCharacterRoundDispatcher::GetMinInitPosition(),
    FCharacterRoundDispatcher::GetMaxInitPosition());

void FCharacterRoundDispatcher::Init(const TArray<TSharedRef<ICharacterBattleDelegate>>& characters)
{
    auto count = characters.Num();
    for (int i = 0; i < count; ++i)
    {
        auto& character = characters[i];
        auto position = GetNextRandomNum();
        RoundInfoArray.Emplace(character.Get(), position);
        character->OnCharacterDead().AddRaw(this, &FCharacterRoundDispatcher::OnCharacterDead);
        character->OnCharacterRevive().AddRaw(this, &FCharacterRoundDispatcher::OnCharacterRevive);
    }
}

void FCharacterRoundDispatcher::OnBattleBegin()
{
    UpdateProgressView();
}

void FCharacterRoundDispatcher::AddCharacter(const TSharedRef<ICharacterBattleDelegate>& character)
{
    auto position = GetNextRandomNum();
    RoundInfoArray.Emplace(character.Get(), position);
    character->OnCharacterDead().AddRaw(this, &FCharacterRoundDispatcher::OnCharacterDead);
    character->OnCharacterRevive().AddRaw(this, &FCharacterRoundDispatcher::OnCharacterRevive);

    if (character->GetPropertyManager().IsAlive())
    {
        UpdateProgressView();
    }
}

// 如果返回0，表示速度超越极限。否则返回时间为为实际需要时间的100倍
inline int32 GetAdvanceTime(const FCharacterRoundInfo& info)
{
    int32 time = 4500 - 4 * info.GetSpeedValue();
    if (time <= 0)
    {
        return 0;
    }
    return time * (100 - info.GetCurrentPosition());
}

ICharacterBattleDelegate& FCharacterRoundDispatcher::MoveToNext()
{
    // 首先取出所有存错的角色信息
    TArray<FCharacterRoundInfo*> infoArray;
    for (auto& info : RoundInfoArray)
    {
        if (info.IsAlive())
        {
            infoArray.Add(&info);
        }
    }
    _ASSERT(infoArray.Num() > 0);

    // TODO: 先计算UI中进度条滑动动画时间，然后启动UI更新，同时阻塞当前线程，直到UI动画完成
    // 行动时间公式：T=4500-4*速，单位为ms
    int32 minIndex = 0;
    int32 minTime = GetAdvanceTime(*infoArray[0]);

    // 找出前进到100%所需最小时间的角色的下标
    auto count = infoArray.Num();
    for (int i = 1; i < count; ++i)
    {
        int32 time = GetAdvanceTime(*infoArray[i]);
        if (time < minTime)
        {
            minTime = time;
            minIndex = i;
        }
        else if (time == minTime)
        {
            if (infoArray[i]->GetCurrentPosition() > infoArray[minIndex]->GetCurrentPosition())
            {
                minIndex = i;
            }
        }
    }
    // minTime = minTime < 0 ? 0 : minTime;

    if (0 == minTime)
    {
        // 将其它同样需要时间为0的角色前进一定进度
        int32 distance = 100 - infoArray[minIndex]->GetCurrentPosition();
        if (0 == distance)
        {
            // 增幅为0，则需要对当前进度为0,1,2...的角色依次进度加一，避免出现0进度角色始终无法被调度到的情况。
            // 下面首先找出一个临界值，所有小于临界值的都需要加一，以保持之前的进度顺序，临界值就是将所有角色进度值
            // 升序排列后从1开始第一个不在整数序列中的值，这样进行加一之后才不会出现本来进度不同的两个角色的进度一样的情况。
            bool zeroExist = infoArray.ContainsByPredicate([](const FCharacterRoundInfo* info)
            {
                int32 time = GetAdvanceTime(*info);
                return time <= 0 && 0 == info->GetCurrentPosition();
            });
            if (zeroExist)
            {
                int32 criticalValue = 0;
                bool exist;
                do
                {
                    ++criticalValue;
                    exist = infoArray.ContainsByPredicate([criticalValue](const FCharacterRoundInfo* info)
                    {
                        int32 time = GetAdvanceTime(*info);
                        return time <= 0 && criticalValue == info->GetCurrentPosition();
                    });
                } while (exist);

                for (int i = 0; i < count; ++i)
                {
                    int32 time = GetAdvanceTime(*infoArray[i]);
                    if (time <= 0 && infoArray[i]->GetCurrentPosition() < criticalValue)
                    {
                        infoArray[i]->AddCurrentPosition(1);
                    }
                }
            }
        }
        else
        {
            // 增幅不为0，直接对每个0时间角色前进对应距离
            for (int i = 0; i < count; ++i)
            {
                int32 time = GetAdvanceTime(*infoArray[i]);
                if (time <= 0)
                {
                    infoArray[i]->AddCurrentPosition(distance);
                }
            }
        }
    }
    else if (minTime >= 100) // 需要1ms以上时间时才对所有角色进行前进移动，否则只移动到100%的那一个
    {
        // 每个角色按照其速度前进一定距离：distance = ( (minTime/100) / time ) * 100，其中time为角色
        // 前进100%时行动时间，化简可得：distance = minTime / time
        for (int i = 0; i < count; ++i)
        {
            int32 time = 4500 - 4 * infoArray[i]->GetSpeedValue();
            int32 distance = minTime / time;
            infoArray[i]->AddCurrentPosition(distance);
        }
    }

    // 所需时间最短的角色直接移动到100%，以修正前面整数计算可能带来的误差
    infoArray[minIndex]->SetCurrentPosition(100);

    // TODO: 等待UI动画完成，角色在时间槽上移动到100%位置
    //
    int32 storyDuration = minTime / 100;
    storyDuration = storyDuration < 500 ? 500 : storyDuration; // 动画最低时长为500ms
    std::this_thread::sleep_for(std::chrono::milliseconds(storyDuration));

    // 将到达100%的即将行动的角色进度reset为0。之所以不是在每次方法开始时将100%角色进度置零，
    // 是考虑到可能会有多个角色同时进度为100%的情况，如果在方法开始置零，就会导致100%进度角色
    // 尚未行动进度就被置零。
    infoArray[minIndex]->SetCurrentPosition(0);
    
    return infoArray[minIndex]->GetCharacter();
}

void FCharacterRoundDispatcher::OnBattleFinished()
{
    auto count = RoundInfoArray.Num();
    for (int i = 0; i < count; ++i)
    {
        auto& character = RoundInfoArray[i].GetCharacter();
        character.OnCharacterDead().RemoveAll(this);
        character.OnCharacterRevive().RemoveAll(this);
    }
}

int32 FCharacterRoundDispatcher::GetNextRandomNum()
{
    return distribution(generator);
}

// TODO: 更新UI的操作
void FCharacterRoundDispatcher::UpdateProgressView()
{
}

void FCharacterRoundDispatcher::OnCharacterDead(const ICharacterBattleDelegate &)
{
    UpdateProgressView();
}

void FCharacterRoundDispatcher::OnCharacterRevive(const ICharacterBattleDelegate& character)
{
    // 复活后行动进度置零
    for (auto& info : RoundInfoArray)
    {
        if (&character == &info.GetCharacter())
        {
            info.SetCurrentPosition(0);
            break;
        }
    }

    UpdateProgressView();
}
