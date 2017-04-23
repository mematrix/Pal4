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

// �������0����ʾ�ٶȳ�Խ���ޡ����򷵻�ʱ��ΪΪʵ����Ҫʱ���100��
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
    // ����ȡ�����д��Ľ�ɫ��Ϣ
    TArray<FCharacterRoundInfo*> infoArray;
    for (auto& info : RoundInfoArray)
    {
        if (info.IsAlive())
        {
            infoArray.Add(&info);
        }
    }
    _ASSERT(infoArray.Num() > 0);

    // TODO: �ȼ���UI�н�������������ʱ�䣬Ȼ������UI���£�ͬʱ������ǰ�̣߳�ֱ��UI�������
    // �ж�ʱ�乫ʽ��T=4500-4*�٣���λΪms
    int32 minIndex = 0;
    int32 minTime = GetAdvanceTime(*infoArray[0]);

    // �ҳ�ǰ����100%������Сʱ��Ľ�ɫ���±�
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
        // ������ͬ����Ҫʱ��Ϊ0�Ľ�ɫǰ��һ������
        int32 distance = 100 - infoArray[minIndex]->GetCurrentPosition();
        if (0 == distance)
        {
            // ����Ϊ0������Ҫ�Ե�ǰ����Ϊ0,1,2...�Ľ�ɫ���ν��ȼ�һ���������0���Ƚ�ɫʼ���޷������ȵ��������
            // ���������ҳ�һ���ٽ�ֵ������С���ٽ�ֵ�Ķ���Ҫ��һ���Ա���֮ǰ�Ľ���˳���ٽ�ֵ���ǽ����н�ɫ����ֵ
            // �������к��1��ʼ��һ���������������е�ֵ���������м�һ֮��Ų�����ֱ������Ȳ�ͬ��������ɫ�Ľ���һ���������
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
            // ������Ϊ0��ֱ�Ӷ�ÿ��0ʱ���ɫǰ����Ӧ����
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
    else if (minTime >= 100) // ��Ҫ1ms����ʱ��ʱ�Ŷ����н�ɫ����ǰ���ƶ�������ֻ�ƶ���100%����һ��
    {
        // ÿ����ɫ�������ٶ�ǰ��һ�����룺distance = ( (minTime/100) / time ) * 100������timeΪ��ɫ
        // ǰ��100%ʱ�ж�ʱ�䣬����ɵã�distance = minTime / time
        for (int i = 0; i < count; ++i)
        {
            int32 time = 4500 - 4 * infoArray[i]->GetSpeedValue();
            int32 distance = minTime / time;
            infoArray[i]->AddCurrentPosition(distance);
        }
    }

    // ����ʱ����̵Ľ�ɫֱ���ƶ���100%��������ǰ������������ܴ��������
    infoArray[minIndex]->SetCurrentPosition(100);

    // TODO: �ȴ�UI������ɣ���ɫ��ʱ������ƶ���100%λ��
    //
    int32 storyDuration = minTime / 100;
    storyDuration = storyDuration < 500 ? 500 : storyDuration; // �������ʱ��Ϊ500ms
    std::this_thread::sleep_for(std::chrono::milliseconds(storyDuration));

    // ������100%�ļ����ж��Ľ�ɫ����resetΪ0��֮���Բ�����ÿ�η�����ʼʱ��100%��ɫ�������㣬
    // �ǿ��ǵ����ܻ��ж����ɫͬʱ����Ϊ100%�����������ڷ�����ʼ���㣬�ͻᵼ��100%���Ƚ�ɫ
    // ��δ�ж����Ⱦͱ����㡣
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

// TODO: ����UI�Ĳ���
void FCharacterRoundDispatcher::UpdateProgressView()
{
}

void FCharacterRoundDispatcher::OnCharacterDead(const ICharacterBattleDelegate &)
{
    UpdateProgressView();
}

void FCharacterRoundDispatcher::OnCharacterRevive(const ICharacterBattleDelegate& character)
{
    // ������ж���������
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
