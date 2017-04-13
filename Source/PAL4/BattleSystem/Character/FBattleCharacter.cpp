// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FBattleCharacter.h"

FBattleCharacter::FBattleCharacter(const TSharedRef<ICharacterBattleDelegate>& character) :
    CharacterDelegate(character),
    TemporaryStatus(character->GetPersistentStatus()),
    RoundManager(character->GetRoundAction()),
    TempStatusManager(*this)
{
}

void FBattleCharacter::OnBattleBegin()
{
    CharacterDelegate->OnBattleBegin(RoundManager, TemporaryStatus);
}

void FBattleCharacter::OnBattleFinished()
{
    CharacterDelegate->OnBattleFinished();
}
