// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FRoleProperty.h"
#include "Primitives/Helper/FStatusInfoAccessHelper.h"


FRoleProperty::FRoleProperty(const TSharedRef<FCharacterInherentInfo>& inherent, const FCharacterStatusInfo& status) :
    ICharacterProperty(),
    InherentInfo(inherent),
    StatusInfo(status),
    PersistentStatus(StatusInfo),
    FavorOfTianhe(0),
    FavorOfLingsha(0),
    FavorOfMengli(0),
    FavorOfZiying(0)
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

void FRoleProperty::SetRoleFavor(ERole role, int32 value)
{
    switch (role)
    {
    case ERole::Tianhe: FavorOfTianhe = value; break;

    case ERole::Lingsha: FavorOfLingsha = value; break;

    case ERole::Mengli: FavorOfMengli = value; break;

    case ERole::Ziying: FavorOfZiying = value; break;

    default: break;
    }
}

void FRoleProperty::AddRoleFavor(ERole role, int32 value)
{
    switch (role)
    {
    case ERole::Tianhe: FavorOfTianhe += value; break;

    case ERole::Lingsha: FavorOfLingsha += value; break;

    case ERole::Mengli: FavorOfMengli += value; break;

    case ERole::Ziying: FavorOfZiying += value; break;

    default: break;
    }
}

int32 FRoleProperty::GetRoleFavor(ERole role) const
{
    switch (role)
    {
    case ERole::Tianhe: return FavorOfTianhe;

    case ERole::Lingsha: return FavorOfLingsha;

    case ERole::Mengli: return FavorOfMengli;

    case ERole::Ziying: return FavorOfZiying;

    default: return 0;
    }
}
