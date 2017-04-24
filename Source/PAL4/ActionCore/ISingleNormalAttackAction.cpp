// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "ISingleNormalAttackAction.h"
#include "CombatSystem/FCombatContext.h"
#include "Exception/FMethodNotImplementedException.h"


void ISingleNormalAttackAction::DoAction()
{
    do
    {
        DoCompleteAttack();
    } while (CanAttackAgain());
}

void ISingleNormalAttackAction::DoOneAttack(ICharacterBattleDelegate& character) const
{
    FBattleContext::GetBattleSystem()->DoAttackAction(*this, character, 0, &ISingleNormalAttackAction::UpdateUI);
}

TSharedRef<FBaseRestorerModel> ISingleNormalAttackAction::ComputeRestorerResult(const ICharacterBattleDelegate&, int32) const
{
    throw FMethodNotImplementedException("ISingleNormalAttackAction::ComputeRestorerResult not implemented");
}

TSharedRef<FBaseStatusModel> ISingleNormalAttackAction::ComputeStatusResult(const ICharacterBattleDelegate&, int32) const
{
    throw FMethodNotImplementedException("ISingleNormalAttackAction::ComputeStatusResult not implemented");
}

void ISingleNormalAttackAction::OnAttackFinishedOverride(const ICharacterBattleDelegate&, const FBaseAttackModel& model, int32 type) const
{
    //
}
