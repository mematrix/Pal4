// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Array.h>
#include <SharedPointer.h>

#include "IBattleStatus.h"
#include "ICharacterRoundDispatcher.h"

/**
 * 
 */
class PAL4_API FBattleSystem
{
public:
    DECLARE_EVENT_OneParam(FBattleSystem, FBattleBeginEvent, const FBattleSystem&);
    DECLARE_EVENT_OneParam(FBattleSystem, FBattleFinishedEvent, const FBattleSystem&);

public:
    FBattleSystem(TArray<TSharedRef<IBattleStatus>>&, TSharedRef<ICharacterRoundDispatcher>&);
    FBattleSystem(const FBattleSystem&) = delete;
	~FBattleSystem();

    FBattleSystem& operator=(const FBattleSystem&) = delete;

    FBattleBeginEvent& OnBattleBegin() { return BattleBeginEvent; }
    FBattleFinishedEvent& OnBattleFinished() { return BattleFinishedEvent; }

    // TArray<TSharedRef<IBattleStatus>>& GetCharacters() { return Characters; }
    const TArray<TSharedRef<IBattleStatus>>& GetCharacters() const { return Characters; }

    void AddCharacter(const TSharedRef<IBattleStatus>& character)
    {
        Characters.Add(character);
    }

    const TSharedRef<ICharacterRoundDispatcher>& GetDispatcher() const { return Dispatcher; }

    void SetDispatcher(const TSharedRef<ICharacterRoundDispatcher>& dispatcher)
    {
        Dispatcher = dispatcher;
    }

    /**
     * 开始进入战斗
     */
    void Run();

private:
    bool BattleIsOver() const;
    bool IsPlayerWinned(TSharedRef<IBattleStatus>&) const;

private:
    FBattleBeginEvent BattleBeginEvent;
    FBattleFinishedEvent BattleFinishedEvent;

    TArray<TSharedRef<IBattleStatus>> Characters;
    TSharedRef<ICharacterRoundDispatcher> Dispatcher;
};
