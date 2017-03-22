// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"
#include "FCharacterRoundManager.h"
#include "ISupportRoundAction.h"

FCharacterRoundManager::FCharacterRoundManager(ISupportRoundAction& action) :
    RoundBeginEvent(),
    RoundFinishedEvent(),
    RoundAction(action),
    RoundFunc(),
    RoundNum(0),
    DelayFuncKey(0)
{
}

FCharacterRoundManager::FCharacterRoundManager(FCharacterRoundManager &&other) :
    RoundBeginEvent(MoveTemp(other.RoundBeginEvent)),
    RoundFinishedEvent(MoveTemp(other.RoundFinishedEvent)),
    RoundAction(other.RoundAction),
    RoundFunc(MoveTemp(other.RoundFunc)),
    RoundNum(other.RoundNum),
    DelayFuncKey(other.DelayFuncKey)
{
    other.RoundAction = GetDefaultRoundAction();
    other.RoundNum = 0;
    other.DelayFuncKey = 0;
}

FCharacterRoundManager & FCharacterRoundManager::operator=(FCharacterRoundManager &&)
{
    // TODO: 在此处插入 return 语句
}

void FCharacterRoundManager::DoRoundAction()
{
    //
}
