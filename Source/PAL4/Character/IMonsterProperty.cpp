// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "IMonsterProperty.h"
#include "Primitives/Model/FMonsterInherentInfo.h"


IMonsterProperty::IMonsterProperty(const FCharacterBasicInfo& info, const FMonsterTypicalInfo& typicalInfo) :
    ICharacterProperty(info),
    MonsterTypicalInfo(typicalInfo)
{
}

bool IMonsterProperty::IsDebuffImmune(EImmune m) const
{
    return (GetMonsterInherentInfo().ImmuneFlags | MonsterTypicalInfo.ImmuneFlags) & static_cast<int32>(m);
}
