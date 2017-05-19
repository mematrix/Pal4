// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FMonsterProperty.h"
#include "Primitives/Helper/FStatusInfoAccessHelper.h"


FMonsterProperty::FMonsterProperty(const TSharedRef<FCharacterInherentInfo>& inherentInfo,
    const TSharedRef<FMonsterInherentInfo>& monsterInherentInfo, const FCharacterBasicInfo& basicInfo,
    const FCharacterStatusInfo& statusInfo, const FMonsterTypicalInfo& typicalInfo) :
    IMonsterProperty(basicInfo, typicalInfo),
    CharacterInherentInfo(inherentInfo),
    MonsterInherentInfo(monsterInherentInfo),
    StatusInfo(statusInfo),
    PersistentStatus(StatusInfo)
{
}

void FMonsterProperty::UpdateStatusInfo(ECharacterStatusType type, int32 value)
{
    FStatusInfoAccessHelper(StatusInfo).SetPropertyValue(type, value);
    PersistentStatus.UpdatePropertyValue(type);
}

void FMonsterProperty::UpdateStatusInfo(const FCharacterStatusInfo& info)
{
    StatusInfo = info;
    PersistentStatus.UpdateAllProperties();
}
