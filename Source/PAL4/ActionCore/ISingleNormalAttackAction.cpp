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

void ISingleNormalAttackAction::DoOneAttack(ICharacterCombatDelegate& character) const
{
    FCombatContext::GetBattleSystem()->DoAttackAction(*this, character, 0, &ISingleNormalAttackAction::UpdateUI);
}

TSharedRef<FBaseRestorerModel> ISingleNormalAttackAction::ComputeRestorerResult(const ICharacterCombatDelegate&, int32) const
{
    throw FMethodNotImplementedException("ISingleNormalAttackAction::ComputeRestorerResult not implemented");
}

TSharedRef<FBaseStatusModel> ISingleNormalAttackAction::ComputeStatusResult(const ICharacterCombatDelegate&, int32) const
{
    throw FMethodNotImplementedException("ISingleNormalAttackAction::ComputeStatusResult not implemented");
}

void ISingleNormalAttackAction::OnAttackFinishedOverride(const ICharacterCombatDelegate&, const FBaseAttackModel& model, int32 type) const
{
    //
}
