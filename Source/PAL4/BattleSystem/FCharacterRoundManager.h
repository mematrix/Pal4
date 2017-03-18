// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ISupportRoundAction.h"
#include "FBattleSystem.h"

/**
 * 
 */
class PAL4_API FCharacterRoundManager
{
    friend class FBattleSystem;

public:
    explicit FCharacterRoundManager(ISupportRoundAction& action) : RoundAction(action) { }

    FCharacterRoundManager(const FCharacterRoundManager&) = delete;

	~FCharacterRoundManager() = default;

    FCharacterRoundManager& operator=(const FCharacterRoundManager&) = delete;

public:
    DECLARE_EVENT_TwoParams(FCharacterRoundManager, FRoundBeginEvent, const FCharacterRoundManager&, uint32)
    DECLARE_EVENT_OneParam(FCharacterRoundManager, FRoundFinishedEvent, const FCharacterRoundManager&)

    FRoundBeginEvent& OnNewRoundBegin() { return RoundBeginEvent; }
    FRoundFinishedEvent& OnRoundFinished() { return RoundFinishedEvent; }

private:
    FRoundBeginEvent RoundBeginEvent;
    FRoundFinishedEvent RoundFinishedEvent;

private:
    ISupportRoundAction& RoundAction;
};
