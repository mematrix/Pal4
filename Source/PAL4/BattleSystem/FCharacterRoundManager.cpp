// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"
#include "FCharacterRoundManager.h"
#include "ISupportRoundAction.h"

FCharacterRoundManager::FCharacterRoundManager(TSharedRef<ISupportRoundAction> action) :
    RoundBeginEvent(),
    RoundFinishedEvent(),
    RoundAction(action),
    RoundFunc(),
    RoundNum(0),
    DelayFuncKey(0),
    RoundStatus(ECharacterRoundStatus::NoAction)
{
}

FCharacterRoundManager::FCharacterRoundManager(FCharacterRoundManager &&other) :
    RoundBeginEvent(MoveTemp(other.RoundBeginEvent)),
    RoundFinishedEvent(MoveTemp(other.RoundFinishedEvent)),
    RoundAction(MoveTemp(other.RoundAction)),
    RoundFunc(MoveTemp(other.RoundFunc)),
    RoundNum(other.RoundNum),
    DelayFuncKey(other.DelayFuncKey),
    RoundStatus(other.RoundStatus)
{
    // other.RoundNum = 0;
    // other.DelayFuncKey = 0;
}

FCharacterRoundManager & FCharacterRoundManager::operator=(FCharacterRoundManager &&other)
{
    RoundBeginEvent = MoveTemp(other.RoundBeginEvent);
    RoundFinishedEvent = MoveTemp(other.RoundFinishedEvent);
    RoundAction = MoveTemp(other.RoundAction);
    RoundFunc = MoveTemp(other.RoundFunc);
    RoundNum = other.RoundNum;
    DelayFuncKey = other.DelayFuncKey;
    RoundStatus = other.RoundStatus;
    return (*this);
}

void FCharacterRoundManager::Swap(FCharacterRoundManager & other)
{
    using std::swap;
    swap(RoundBeginEvent, other.RoundBeginEvent);
    swap(RoundFinishedEvent, other.RoundFinishedEvent);
    swap(RoundAction, other.RoundAction);
    RoundFunc.swap(other.RoundFunc);
    swap(RoundNum, other.RoundNum);
    swap(DelayFuncKey, other.DelayFuncKey);
    swap(RoundStatus, other.RoundStatus);
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
    //
}
