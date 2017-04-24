// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCombatCharacter.h"

FBattleCharacter::FBattleCharacter(const TSharedRef<ICharacterBattleDelegate>& character) :
    ICharacterBattleContext(),
    CharacterDelegate(character),
    RoundManager(character->GetRoundAction()),
    TempStatusManager(character.Get()),
    ActionInterceptor(character.Get())
{
}

void FBattleCharacter::OnBattleBegin()
{
    CharacterDelegate->BeginBattle(*this);
}

void FBattleCharacter::OnBattleFinished()
{
    CharacterDelegate->FinishBattle();
}
