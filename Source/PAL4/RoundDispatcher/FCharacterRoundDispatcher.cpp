// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <random>

#include "FCharacterRoundDispatcher.h"

std::default_random_engine generator;
std::uniform_int_distribution<int32> distribution(FCharacterRoundDispatcher::GetMinInitPosition(),
    FCharacterRoundDispatcher::GetMaxInitPosition());

void FCharacterRoundDispatcher::OnBattleBegin(const TArray<TSharedRef<FBattleCharacter>>& characters)
{
    auto ondead = std::bind(&FCharacterRoundDispatcher::OnCharacterDead, this, std::placeholders::_1);
    auto onrevive = std::bind(&FCharacterRoundDispatcher::OnCharacterRevive, this, std::placeholders::_1);

    auto count = characters.Num();
    for (int i = 0; i < count; ++i)
    {
        auto& character = characters[i];
        auto position = GetNextRandomNum();
        RoundInfoArray.Emplace(character.Get(), position);
        character->GetCharacterDelegate().SetOnDeadCallback(ondead);
        character->GetCharacterDelegate().SetOnReviveCallback(onrevive);
    }

    UpdateProgressView();
}

void FCharacterRoundDispatcher::AddCharacter(const TSharedRef<FBattleCharacter>& character)
{
    auto position = GetNextRandomNum();
    RoundInfoArray.Emplace(character.Get(), position);
    character->GetCharacterDelegate().SetOnDeadCallback(
        std::bind(&FCharacterRoundDispatcher::OnCharacterDead, this, std::placeholders::_1));
    character->GetCharacterDelegate().SetOnReviveCallback(
        std::bind(&FCharacterRoundDispatcher::OnCharacterRevive, this, std::placeholders::_1));

    if (character->GetCharacterDelegate().GetPropertyManager().IsAlive())
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

FBattleCharacter& FCharacterRoundDispatcher::MoveToNext()
{
    // TODO: 先计算UI中进度条滑动动画时间，然后启动UI更新，同时阻塞当前线程，直到UI动画完成
    // 行动时间公式：T=4500-4*速，单位为ms
    int32 minIndex = 0;
    int32 minTime = GetAdvanceTime(RoundInfoArray[0]);

    // 找出前进到100%所需最小时间的角色的下标
    auto count = RoundInfoArray.Num();
    for (int i = 1; i < count; ++i)
    {
        int32 time = GetAdvanceTime(RoundInfoArray[i]);
        if (time < minTime)
        {
            minTime = time;
            minIndex = i;
        }
        else if (time == minTime)
        {
            if (RoundInfoArray[i].GetCurrentPosition() > RoundInfoArray[minIndex].GetCurrentPosition())
            {
                minIndex = i;
            }
        }
    }
    // minTime = minTime < 0 ? 0 : minTime;

    if (0 == minTime)
    {
        // 将其它同样需要时间为0的角色前进一定进度
        int32 distance = 100 - RoundInfoArray[minIndex].GetCurrentPosition();
        if (0 == distance)
        {
            // 增福为0，则需要对当前进度为0,1,2...的角色依次进度加一，避免出现0进度角色始终无法被调度到的情况。
            // 下面首先找出需要加一的临界值，所有小于临界值的都需要加一，以保持之前的进度顺序，临界值
            // 就是最小的进度不存在的值，所以进行加一之后才不会出现本来进度不同的两个角色的进度一样的情况。
            bool zeroExist = RoundInfoArray.ContainsByPredicate([](const FCharacterRoundInfo& info)
            {
                int32 time = GetAdvanceTime(info);
                return time <= 0 && 0 == info.GetCurrentPosition();
            });
            if (zeroExist)
            {
                int32 criticalValue = 0;
                bool exist;
                do
                {
                    ++criticalValue;
                    exist = RoundInfoArray.ContainsByPredicate([criticalValue](const FCharacterRoundInfo& info)
                    {
                        int32 time = GetAdvanceTime(info);
                        return time <= 0 && criticalValue == info.GetCurrentPosition();
                    });
                } while (exist);

                for (int i = 0; i < count; ++i)
                {
                    int32 time = GetAdvanceTime(RoundInfoArray[i]);
                    if (time <= 0 && RoundInfoArray[i].GetCurrentPosition() < criticalValue)
                    {
                        RoundInfoArray[i].AddCurrentPosition(1);
                    }
                }
            }
        }
        else
        {
            // 增福不为0，直接对每个0时间角色前进对应距离
            for (int i = 0; i < count; ++i)
            {
                int32 time = GetAdvanceTime(RoundInfoArray[i]);
                if (time <= 0)
                {
                    RoundInfoArray[i].AddCurrentPosition(distance);
                }
            }
        }
    }
    else if (minTime >= 100) // 需要1ms以上时间时才对所有角色进行前进移动，否则只移动到100%的那一个
    {
        //
    }
}

void FCharacterRoundDispatcher::OnBattleFinished()
{
    auto count = RoundInfoArray.Num();
    for (int i = 0; i < count; ++i)
    {
        auto& character = RoundInfoArray[i].GetCharacter().GetCharacterDelegate();
        character.SetOnDeadCallback(nullptr);
        character.SetOnReviveCallback(nullptr);
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

void FCharacterRoundDispatcher::OnCharacterRevive(const ICharacterBattleDelegate &)
{
    UpdateProgressView();
}
