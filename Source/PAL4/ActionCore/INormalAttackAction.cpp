// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "INormalAttackAction.h"
#include "BattleSystem/FBattleContext.h"
#include "Exception/FMethodNotImplementedException.h"


void INormalAttackAction::DoAction()
{
    do
    {
        DoCompleteAttack();
    } while (CanAttackAgain());
}

void INormalAttackAction::DoOneAttack(ICharacterBattleDelegate& character) const
{
    FBattleContext::GetBattleSystem()->DoAttackAction(*this, character, 0, &INormalAttackAction::UpdateUI);
}

TSharedRef<FBaseRestorerModel> INormalAttackAction::ComputeRestorerResult(const ICharacterBattleDelegate&, int32) const
{
    throw FMethodNotImplementedException("INormalAttackAction::ComputeRestorerResult not implemented");
}

TSharedRef<FBaseStatusModel> INormalAttackAction::ComputeStatusResult(const ICharacterBattleDelegate&, int32) const
{
    throw FMethodNotImplementedException("INormalAttackAction::ComputeStatusResult not implemented");
}

void INormalAttackAction::OnAttackFinishedOverride(const ICharacterBattleDelegate&, const FBaseAttackModel& model, int32 type) const
{
    //
}
