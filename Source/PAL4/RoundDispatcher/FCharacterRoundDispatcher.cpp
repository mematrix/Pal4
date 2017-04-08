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

FBattleCharacter& FCharacterRoundDispatcher::MoveToNext()
{
    // TODO: �ȼ���UI�н�������������ʱ�䣬Ȼ������UI���£�ͬʱ������ǰ�̣߳�ֱ��UI�������
    // �ж�ʱ�乫ʽ��T=4500-4*�٣���λΪms
    int32 minIndex = 0;
    int32 minTime = GetAdvanceTime(RoundInfoArray[0]);

    // �ҳ�ǰ����100%������Сʱ��Ľ�ɫ���±�
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
        // ������ͬ����Ҫʱ��Ϊ0�Ľ�ɫǰ��һ������
        int32 distance = 100 - RoundInfoArray[minIndex].GetCurrentPosition();
        if (0 == distance)
        {
            // ����Ϊ0������Ҫ�Ե�ǰ����Ϊ0,1,2...�Ľ�ɫ���ν��ȼ�һ���������0���Ƚ�ɫʼ���޷������ȵ��������
            // ���������ҳ���Ҫ��һ���ٽ�ֵ������С���ٽ�ֵ�Ķ���Ҫ��һ���Ա���֮ǰ�Ľ���˳���ٽ�ֵ
            // ������С�Ľ��Ȳ����ڵ�ֵ�����Խ��м�һ֮��Ų�����ֱ������Ȳ�ͬ��������ɫ�Ľ���һ���������
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
            // ������Ϊ0��ֱ�Ӷ�ÿ��0ʱ���ɫǰ����Ӧ����
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
    else if (minTime >= 100) // ��Ҫ1ms����ʱ��ʱ�Ŷ����н�ɫ����ǰ���ƶ�������ֻ�ƶ���100%����һ��
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

// TODO: ����UI�Ĳ���
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
