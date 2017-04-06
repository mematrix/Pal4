// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <algorithm>

#include "FBattleSystem.h"
#include "CharacterBridge/IRoundActionHandler.h"
#include "Character/FCharacterPropertyManager.h"


FBattleSystem::FBattleSystem(const TArray<TSharedRef<ICharacterBattleDelegate>>& characters,
    const TSharedRef<ICharacterRoundDispatcher>& dispatcher) :
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
        RoundManagers.Add(MakeShared<FCharacterRoundManager>(Characters[i]));
    }
}

FBattleSystem::~FBattleSystem()
{
}

void FBattleSystem::AddCharacter(const TSharedRef<ICharacterBattleDelegate>& character)
{
    RoundManagers.Add(MakeShared<FCharacterRoundManager>(character));
    Characters.Add(character);
}

void FBattleSystem::Run()
{
    if (BattleBeginEvent.IsBound())
    {
        BattleBeginEvent.Broadcast(*this);
    }

    // 不应该出现这种情况
    _ASSERT(!BattleIsOver());

    ICharacterBattleDelegate* characterActLast = nullptr;
    while (!BattleIsOver())
    {
        auto& character = Dispatcher->MoveToNext(Characters).Get();
        characterActLast = &character;
        if (CharacterWillActEvent.IsBound())
        {
            CharacterWillActEvent.Broadcast(*this, character);
        }

        auto roundManager = character.GetRoundManager();
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
    if (isAnyNonPlayerAlive && !isAnyPlayerAlive)
    {
        return false;
    }
    return CharacterActLast->GetPropertyManager().IsPlayer();
}

bool FBattleSystem::IsPlayerWinned(TSharedRef<ICharacterBattleDelegate>& lastCharacter) const
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
