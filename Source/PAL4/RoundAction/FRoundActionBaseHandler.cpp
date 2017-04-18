// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FRoundActionBaseHandler.h"
#include "Util/EventUtil.h"
#include "BattleSystem/ActionCore/ISingleAction.h"

FRoundActionBaseHandler::FRoundActionBaseHandler(const TSharedRef<ICharacterBattleDelegate>& character) :
    BeforeAttackEvent(),
    OnAttackEvent(),
    AfterAttackEvent(),
    Character(character)
{
}

void FRoundActionBaseHandler::OnAction()
{
    auto action = GetAttackAction();

    InvokeEvent(BeforeAttackEvent, *this, action.Get());
    action->BeforeDoAttack();

    InvokeEvent(OnAttackEvent, *this, action.Get());
    action->DoAttack();

    action->AfterDoAttack();
    InvokeEvent(AfterAttackEvent, *this, action.Get());
}
