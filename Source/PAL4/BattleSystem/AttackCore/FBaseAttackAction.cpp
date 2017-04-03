// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FBaseAttackAction.h"
#include "Util/EventUtil.h"

FBaseAttackAction::FBaseAttackAction() :
    Character(nullptr),
    BeforeAttackEvent(),
    OnAttackEvent(),
    AfterAttackEvent()
{
}

void FBaseAttackAction::BeforeDoAttack(const ICharacterBattleStatus& character)
{
    Character = &character;
//    if (BeforeAttackEvent.IsBound())
//    {
//        BeforeAttackEvent.Broadcast(*this, character);
//    }
    InvokeEvent(BeforeAttackEvent, *this, character);
}

void FBaseAttackAction::DoAttack()
{
    if (Character && OnAttackEvent.IsBound())
    {
        OnAttackEvent.Broadcast(*this, *Character);
    }
}

void FBaseAttackAction::AfterDoAttack()
{
    if (Character && AfterAttackEvent.IsBound())
    {
        AfterAttackEvent.Broadcast(*this, *Character);
    }
    Character = nullptr;
}

