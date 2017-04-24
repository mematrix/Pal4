// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCombatCharacter.h"

FCombatCharacter::FCombatCharacter(const TSharedRef<ICharacterCombatDelegate>& character) :
    ICharacterCombatContext(),
    CharacterDelegate(character),
    RoundManager(character->GetRoundAction()),
    TempStatusManager(character.Get()),
    ActionInterceptor(character.Get())
{
}

void FCombatCharacter::OnBattleBegin()
{
    CharacterDelegate->BeginBattle(*this);
}

void FCombatCharacter::OnBattleFinished()
{
    CharacterDelegate->FinishBattle();
}
