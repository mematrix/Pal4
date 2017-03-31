// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <algorithm>

#include "FBattleSystem.h"
#include "ISupportRoundAction.h"
#include "Character/FCharacterPropertyManager.h"


FBattleSystem::FBattleSystem(TArray<TSharedRef<IBattleStatus>>& characters, TSharedRef<ICharacterRoundDispatcher>& dispatcher) :
    BattleBeginEvent(),
    BattleFinishedEvent(),
    CharacterWillActEvent(),
    CharacterFinishActEvent(),
    Characters(characters),
    Dispatcher(dispatcher),
    RoundManagers(),
    CharacterActLast(nullptr)
{
    int32 count = Characters.Num();
    RoundManagers.Reserve(count);
    for (int i = 0; i < count; ++i)
    {
        auto& roundAction = Characters[i]->GetRoundAction();
        RoundManagers.Add(MakeShared<FCharacterRoundManager>(roundAction));
    }
}

FBattleSystem::~FBattleSystem()
{
}

void FBattleSystem::AddCharacter(const TSharedRef<IBattleStatus>& character)
{
    auto& roundManager = MakeShared<FCharacterRoundManager>(character->GetRoundAction());
    RoundManagers.Add(MoveTemp(roundManager));
    Characters.Add(character);
}

void FBattleSystem::Run()
{
    if (BattleBeginEvent.IsBound())
    {
        BattleBeginEvent.Broadcast(*this);
    }

    // 不应该出现这种情况
    if (BattleIsOver())
    {
        _ASSERT(0);
    }

    IBattleStatus* characterActLast = nullptr;
    while (!BattleIsOver())
    {
        auto& character = Dispatcher->MoveToNext(Characters).Get();
        characterActLast = &character;
        if (CharacterWillActEvent.IsBound())
        {
            CharacterWillActEvent.Broadcast(*this, character);
        }

        auto roundManager = character.GetRoundAction().GetRoundManager();
        roundManager->DoRoundAction();
        if (CharacterFinishActEvent.IsBound())
        {
            CharacterFinishActEvent.Broadcast(*this, character);
        }
    }
    CharacterActLast = characterActLast;

    if (BattleFinishedEvent.IsBound())
    {
        BattleFinishedEvent.Broadcast(*this);
    }
}

bool FBattleSystem::BattleIsOver() const
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

    return !(isAnyPlayerAlive && isAnyNonPlayerAlive);
}

bool FBattleSystem::IsPlayerWinned() const
{
    if (nullptr == CharacterActLast)
    {
        return false;
    }

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
    return CharacterActLast->GetPropertyManager().IsPlayer();
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
