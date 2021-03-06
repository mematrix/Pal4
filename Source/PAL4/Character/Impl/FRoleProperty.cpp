// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FRoleProperty.h"
#include "Primitives/Helper/FStatusInfoAccessHelper.h"


FRoleProperty::FRoleProperty(const TSharedRef<FCharacterInherentInfo>& inherent, const FCharacterBasicInfo& info,
    const FCharacterStatusInfo& status, uint32 favors, uint8 initMagicPoint) :
    IRoleProperty(info, favors, initMagicPoint),
    InherentInfo(inherent),
    StatusInfo(status),
    PersistentStatus(StatusInfo)
{
}

void FRoleProperty::UpdateStatusInfo(ECharacterStatusType type, int32 value)
{
    FStatusInfoAccessHelper(StatusInfo).SetPropertyValue(type, value);
    PersistentStatus.UpdatePropertyValue(type);
}

void FRoleProperty::UpdateStatusInfo(const FCharacterStatusInfo& info)
{
    StatusInfo = info;
    PersistentStatus.UpdateAllProperties();
}
