// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <stdexcept>
#include "FCharacterRoundManager.h"
#include "CharacterBridge/IRoundActionHandler.h"

FCharacterRoundManager::FCharacterRoundManager(const TSharedRef<IRoundActionHandler>& action) :
    RoundBeginEvent(),
    RoundFinishedEvent(),
    RoundAction(action),
    RoundFunc(),
    RoundNum(0),
    RoundStatus(ECharacterRoundStatus::NoAction),
    DelayFuncKey(0)
{
    if (nullptr != action->RoundManager)
    {
        throw std::invalid_argument("Action already has a round manager");
    }

    RoundAction->RoundManager = this;
}

FCharacterRoundManager::FCharacterRoundManager(FCharacterRoundManager &&other) :
    RoundBeginEvent(MoveTemp(other.RoundBeginEvent)),
    RoundFinishedEvent(MoveTemp(other.RoundFinishedEvent)),
    RoundAction(MoveTemp(other.RoundAction)),
    RoundFunc(MoveTemp(other.RoundFunc)),
    RoundNum(other.RoundNum),
    RoundStatus(other.RoundStatus),
    DelayFuncKey(other.DelayFuncKey)
{
    RoundAction->RoundManager = this;
}

FCharacterRoundManager::~FCharacterRoundManager()
{
    if (this == RoundAction->RoundManager)
    {
        RoundAction->RoundManager = nullptr;
    }
}

FCharacterRoundManager & FCharacterRoundManager::operator=(FCharacterRoundManager &&other)
{
    if (&other == this)
    {
        return (*this);
    }

    RoundBeginEvent = MoveTemp(other.RoundBeginEvent);
    RoundFinishedEvent = MoveTemp(other.RoundFinishedEvent);
    RoundAction = MoveTemp(other.RoundAction);
    RoundFunc = MoveTemp(other.RoundFunc);
    RoundNum = other.RoundNum;
    DelayFuncKey = other.DelayFuncKey;
    RoundStatus = other.RoundStatus;
    RoundAction->RoundManager = this;

    return (*this);
}

void FCharacterRoundManager::Swap(FCharacterRoundManager & other)
{
    using std::swap;

    if (&other == this)
    {
        return;
    }

    swap(RoundBeginEvent, other.RoundBeginEvent);
    swap(RoundFinishedEvent, other.RoundFinishedEvent);
    swap(RoundAction, other.RoundAction);
    RoundFunc.swap(other.RoundFunc);
    swap(RoundNum, other.RoundNum);
    swap(DelayFuncKey, other.DelayFuncKey);
    swap(RoundStatus, other.RoundStatus);

    RoundAction->SwapManager(other.RoundAction.Get());
}

uint32 FCharacterRoundManager::AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, std::function<void()> func)
{
    uint32 key = ++DelayFuncKey;
    RoundFunc.emplace(key, RoundNum + delayNum, callWhenBegin, MoveTemp(func));
    return key;
}

uint32 FCharacterRoundManager::AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, std::function<void()> func)
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
        RoundFunc.emplace(key, roundNum, callWhenBegin, MoveTemp(func));
        return key;
    }
}

void FCharacterRoundManager::RemoveDelayCallFunc(uint32 key)
{
    RoundFunc.remove([key](const FDelayCallFuncWrapper& funcWrapper) -> bool {
        return key == funcWrapper.Key;
    });
}

void FCharacterRoundManager::DoRoundAction()
{
    ++RoundNum;

    RoundStatus = ECharacterRoundStatus::BeforeAction;
    while (RoundFunc.top().RoundTimeWhenCall < RoundNum)
    {
        RoundFunc.pop();
    }
    while (RoundFunc.top().RoundTimeWhenCall == RoundNum && RoundFunc.top().CallWhenRoundBegin)
    {
        auto &func = RoundFunc.top().DelayCalledFunc;
        if (func)
        {
            func();
        }

        RoundFunc.pop();
    }
    RoundAction->OnNewRoundBegin(RoundNum);

    if (RoundBeginEvent.IsBound())
    {
        RoundBeginEvent.Broadcast(*this, RoundNum);
    }

    RoundStatus = ECharacterRoundStatus::OnAction;
    RoundAction->OnAction();

    RoundStatus = ECharacterRoundStatus::PostAction;
    while (RoundFunc.top().RoundTimeWhenCall == RoundNum && !RoundFunc.top().CallWhenRoundBegin)
    {
        auto &func = RoundFunc.top().DelayCalledFunc;
        if (func)
        {
            func();
        }

        RoundFunc.pop();
    }
    RoundAction->OnRoundFinished();

    if (RoundFinishedEvent.IsBound())
    {
        RoundFinishedEvent.Broadcast(*this);
    }

    RoundStatus = ECharacterRoundStatus::NoAction;
}


void swap(FCharacterRoundManager::FDelayCallFuncWrapper& left, FCharacterRoundManager::FDelayCallFuncWrapper& right)
    noexcept(noexcept(left.Swap(right)))
{
    left.Swap(right);
}

namespace std
{
    template<> void swap<FCharacterRoundManager>(FCharacterRoundManager& left, FCharacterRoundManager& right)
        noexcept(noexcept(left.Swap(right)))
    {
        left.Swap(right);
    }
}

