// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <algorithm>

#include "FBattleSystem.h"
#include "Character/FCharacterPropertyManager.h"


FBattleSystem::FBattleSystem(TArray<TSharedRef<IBattleStatus>>& characters, TSharedRef<ICharacterRoundDispatcher>& dispatcher) :
    Characters(characters),
    Dispatcher(dispatcher)
{
}

FBattleSystem::~FBattleSystem()
{
}

void FBattleSystem::Run()
{
    if (BattleBeginEvent.IsBound())
    {
        BattleBeginEvent.Broadcast(*this);
    }

    //
}

bool FBattleSystem::BattleIsOver() const
{
    bool isAnyPlayerAlive = false;
    bool isAnyNonPlayerAlive = false;
    for (int i = 0; i < Characters.Num(); ++i)
    {
        auto& manager = Characters[i]->GetPropertyManager();
        if (manager.IsPlayer)
        {
            isAnyPlayerAlive = isAnyPlayerAlive || manager.IsAlive();
        }
        else
        {
            isAnyNonPlayerAlive = isAnyNonPlayerAlive || manager.IsAlive();
        }
    }

    return !(isAnyPlayerAlive && isAnyNonPlayerAlive);
}

bool FBattleSystem::IsPlayerWinned(TSharedRef<IBattleStatus>& lastCharacter) const
{
    bool isAnyPlayerAlive = false;
    bool isAnyNonPlayerAlive = false;
    for (int i = 0; i < Characters.Num(); ++i)
    {
        auto& manager = Characters[i]->GetPropertyManager();
        if (manager.IsPlayer())
        {
            isAnyPlayerAlive = isAnyPlayerAlive || manager.IsAlive();
        }
        else
        {
            isAnyNonPlayerAlive = isAnyNonPlayerAlive || manager.IsAlive();
        }
    }

    if (isAnyPlayerAlive && !isAnyNonPlayerAlive)
    {
        return true;
    }
    else if (isAnyNonPlayerAlive && !isAnyPlayerAlive)
    {
        return false;
    }
    
    return lastCharacter->GetPropertyManager().IsPlayer();
}
