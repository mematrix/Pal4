// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "IRoleProperty.h"


IRoleProperty::IRoleProperty(const FCharacterBasicInfo& info, int32 favors[4], int32 initMagicPoint) :
    ICharacterProperty(info),
    FavorOfTianhe(favors[0]),
    FavorOfLingsha(favors[1]),
    FavorOfMengli(favors[2]),
    FavorOfZiying(favors[3]),
    InitMagicPoint(initMagicPoint)
{
}

void IRoleProperty::SetRoleFavor(ERole role, int32 value)
{
    switch (role)
    {
    case ERole::Tianhe: FavorOfTianhe = value; break;

    case ERole::Lingsha: FavorOfLingsha = value; break;

    case ERole::Mengli: FavorOfMengli = value; break;

    case ERole::Ziying: FavorOfZiying = value; break;
    }
}

void IRoleProperty::AddRoleFavor(ERole role, int32 value)
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

int32 IRoleProperty::GetRoleFavor(ERole role) const
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
