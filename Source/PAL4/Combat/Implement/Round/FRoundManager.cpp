// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FRoundManager.h"
#include "Combat/Interface/Character/ICharacterDelegate.h"
#include "Combat/Interface/Character/ICombatContext.h"
#include "Combat/Interface/Character/IStatusManager.h"
#include "Combat/Interface/Character/ITemporaryStatus.h"
#include "Combat/Interface/Round/IRoundActionHandler.h"


FRoundManager::FRoundManager(ICharacterDelegate& character) :
    IRoundManager(),
    Character(character),
    DelayRoundFuncs(),
    RoundFuncs(),
    FuncKey(0)
{
}

uint32 FRoundManager::AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, const std::function<void()>& func)
{
    uint32 key = ++FuncKey;
    uint32 roundNum = RoundNum + delayNum;
    DelayRoundFuncs.emplace(key, roundNum, callWhenBegin, func);
    return key;
}

uint32 FRoundManager::AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, const std::function<void()>& func)
{
    // 回合数已过。或者处于当前回合，但是已经没有调用时机了：要求在回合开始调用、或者要求在结束调用但是现在已经处于结束状态了
    if (roundNum < RoundNum ||
        roundNum == RoundNum && (callWhenBegin || RoundStatus == ERoundStatus::PostAction || RoundStatus == ERoundStatus::NoAction))
    {
        if (callIfPast && func)
        {
            func();
        }

        return 0;
    }

    uint32 key = ++FuncKey;
    DelayRoundFuncs.emplace(key, roundNum, callWhenBegin, func);
    return key;
}

void FRoundManager::RemoveDelayCallFunc(uint32 key)
{
    DelayRoundFuncs.remove([key](const FRoundFuncWrapper& funcWrapper) -> bool {
        return key == funcWrapper.Key;
    });
}

uint32 FRoundManager::AddRoundFunc(bool callWhenBegin, const std::function<void()>& func)
{
    uint32 key = ++FuncKey;
    RoundFuncs.emplace_back(key, 0, callWhenBegin, func);
    return key;
}

void FRoundManager::RemoveRoundFunc(uint32 key)
{
    RoundFuncs.remove_if([key](const FRoundFuncWrapper& funcWrapper) -> bool {
        return key == funcWrapper.Key;
    });
}

void FRoundManager::DoRoundAction()
{
    ++RoundNum;

    RoundStatus = ERoundStatus::BeforeAction;
    while (DelayRoundFuncs.top().RoundNumWhenCall < RoundNum)
    {
        DelayRoundFuncs.pop();
    }
    while (DelayRoundFuncs.top().RoundNumWhenCall == RoundNum && DelayRoundFuncs.top().CallWhenRoundBegin)
    {
        auto func = DelayRoundFuncs.top().Func;
        DelayRoundFuncs.pop();

        if (func)
        {
            func();
        }
    }
    for (const auto& wrapper : RoundFuncs)
    {
        if (wrapper.CallWhenRoundBegin && wrapper.Func)
        {
            wrapper.Func();
        }
    }

    auto& roundAction = Character.GetRoundAction();
    roundAction.OnNewRoundBegin(RoundNum);
    if (RoundBeginEvent.IsBound())
    {
        RoundBeginEvent.Broadcast(*this, RoundNum);
    }

    auto debuff = Character.GetContext()->GetStatusManager().GetTempStatus().GetDebuffStatus();
    bool shouldSkipAction = EDebuff::Ding == debuff || EDebuff::Mian == debuff;
    if (!shouldSkipAction)
    {
        RoundStatus = ERoundStatus::OnAction;
        roundAction.DoAction();
    }

    RoundStatus = ERoundStatus::PostAction;
    roundAction.OnRoundFinished();
    if (RoundFinishedEvent.IsBound())
    {
        RoundFinishedEvent.Broadcast(*this, RoundNum);
    }

    while (DelayRoundFuncs.top().RoundNumWhenCall == RoundNum && DelayRoundFuncs.top().CallWhenRoundBegin)
    {
        DelayRoundFuncs.pop();
    }
    while (DelayRoundFuncs.top().RoundNumWhenCall == RoundNum && !DelayRoundFuncs.top().CallWhenRoundBegin)
    {
        auto func = DelayRoundFuncs.top().Func;
        DelayRoundFuncs.pop();

        if (func)
        {
            func();
        }
    }
    for (const auto& wrapper : RoundFuncs)
    {
        if (!wrapper.CallWhenRoundBegin && wrapper.Func)
        {
            wrapper.Func();
        }
    }

    RoundStatus = ERoundStatus::NoAction;
}
