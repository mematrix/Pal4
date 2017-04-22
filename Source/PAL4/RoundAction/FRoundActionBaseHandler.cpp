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
    action->BeforeDoAction();

    InvokeEvent(OnAttackEvent, *this, action.Get());
    action->DoAction();

    action->AfterDoAction();
    InvokeEvent(AfterAttackEvent, *this, action.Get());
}
