// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "IMonsterProperty.h"
#include "../Model/FMonsterInherentInfo.h"


IMonsterProperty::IMonsterProperty(const FCharacterBasicInfo& info, const FMonsterImmuneInfo& immuneInfo) :
    ICharacterProperty(info),
    ImmuneInfo(immuneInfo)
{
}

bool IMonsterProperty::IsDebuffImmune(EImmune m) const
{
    return (GetMonsterInherentInfo().ImmuneFlags | ImmuneInfo.ImmuneFlags) & static_cast<int32>(m);
}
