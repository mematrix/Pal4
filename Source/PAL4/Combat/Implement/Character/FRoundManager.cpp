// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FRoundManager.h"
#include "Combat/Interface/Round/IRoundActionHandler.h"

FRoundManager::FRoundManager(IRoundActionHandler& action) :
    IRoundManager(),
    RoundAction(action),
    RoundFunc(),
    DelayFuncKey(0)
{
}

//void FRoundManager::Swap(FRoundManager& other)
//{
//    using std::swap;
//
//    if (&other == this)
//    {
//        return;
//    }
//
//    swap(RoundBeginEvent, other.RoundBeginEvent);
//    swap(RoundFinishedEvent, other.RoundFinishedEvent);
//    swap(RoundAction, other.RoundAction);
//    RoundFunc.swap(other.RoundFunc);
//    swap(RoundNum, other.RoundNum);
//    swap(DelayFuncKey, other.DelayFuncKey);
//    swap(RoundStatus, other.RoundStatus);
//}

uint32 FRoundManager::AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, const std::function<void()>& func)
{
    uint32 key = ++DelayFuncKey;
    uint32 roundNum = RoundNum + delayNum;
    RoundFunc.emplace(key, roundNum, callWhenBegin, func);
    return key;
}

uint32 FRoundManager::AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, const std::function<void()>& func)
{
    // 回合数已过。或者处于当前回合，但是已经没有调用时机了：要求在回合开始调用、或者要求在结束调用但是现在已经处于结束状态了
    if (roundNum < RoundNum ||
        (roundNum == RoundNum && (callWhenBegin || RoundStatus != ECharacterRoundStatus::PostAction || RoundStatus != ECharacterRoundStatus::NoAction)))
    {
        if (callIfPast && func)
        {
            func();
        }

        return 0;
    }
    else
    {
        uint32 key = ++DelayFuncKey;
        RoundFunc.emplace(key, roundNum, callWhenBegin, func);
        return key;
    }
}

void FRoundManager::RemoveDelayCallFunc(uint32 key)
{
    RoundFunc.remove([key](const FDelayCallFuncWrapper& funcWrapper) -> bool {
        return key == funcWrapper.Key;
    });
}

void FRoundManager::DoRoundAction(bool shouldSkipAction)
{
    ++RoundNum;

    RoundStatus = ECharacterRoundStatus::BeforeAction;
    while (RoundFunc.top().RoundNumWhenCall < RoundNum)
    {
        RoundFunc.pop();
    }
    while (RoundFunc.top().RoundNumWhenCall == RoundNum && RoundFunc.top().CallWhenRoundBegin)
    {
        auto &func = RoundFunc.top().DelayCalledFunc;
        if (func)
        {
            func();
        }

        RoundFunc.pop();
    }
    RoundAction.OnNewRoundBegin(RoundNum);

    if (RoundBeginEvent.IsBound())
    {
        RoundBeginEvent.Broadcast(*this, RoundNum);
    }

    RoundStatus = ECharacterRoundStatus::OnAction;
    if (!shouldSkipAction)
    {
        RoundAction.DoAction();
    }

    RoundStatus = ECharacterRoundStatus::PostAction;
    RoundAction.OnRoundFinished();

    if (RoundFinishedEvent.IsBound())
    {
        RoundFinishedEvent.Broadcast(*this, RoundNum);
    }
    while (RoundFunc.top().RoundNumWhenCall == RoundNum && !RoundFunc.top().CallWhenRoundBegin)
    {
        auto &func = RoundFunc.top().DelayCalledFunc;
        if (func)
        {
            func();
        }

        RoundFunc.pop();
    }

    RoundStatus = ECharacterRoundStatus::NoAction;
}


void swap(FRoundManager::FDelayCallFuncWrapper& left, FRoundManager::FDelayCallFuncWrapper& right)
    noexcept(noexcept(left.Swap(right)))
{
    left.Swap(right);
}

//namespace std
//{
//    template<> void swap<FRoundManager>(FRoundManager& left, FRoundManager& right)
//        noexcept(noexcept(left.Swap(right)))
//    {
//        left.Swap(right);
//    }
//}

