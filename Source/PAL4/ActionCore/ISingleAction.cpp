// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "ISingleAction.h"
#include "CombatDelegate/Character/ICharacterBattleDelegate.h"


void ISingleAction::OnAttackFinished(const ICharacterBattleDelegate& character, const FBaseAttackModel& model, int32 type) const
{
    OnAttackFinishedOverride(character, model, type);
    Actor.OnAttackActionFinished(*this, character, model, type);
}

void ISingleAction::OnRestorerFinished(const ICharacterBattleDelegate& character, const FBaseRestorerModel& model, int32 type) const
{
    OnRestorerFinishedOverride(character, model, type);
    Actor.OnRestorerActionFinished(*this, character, model, type);
}

void ISingleAction::OnStatusFinished(const ICharacterBattleDelegate& character, const FBaseStatusModel& model, int32 type) const
{
    OnStatusFinishedOverride(character, model, type);
    Actor.OnStatusActionFinished(*this, character, model, type);
}
