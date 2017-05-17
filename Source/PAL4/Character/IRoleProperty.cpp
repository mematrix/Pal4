// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "IRoleProperty.h"


IRoleProperty::IRoleProperty(const FCharacterBasicInfo& info, uint32 favors, uint8 initMagicPoint) :
    ICharacterProperty(info),
    FavorOfTianhe(static_cast<uint8>(favors >> 24)),
    FavorOfLingsha(static_cast<uint8>((favors & 0x00ff0000) >> 16)),
    FavorOfMengli(static_cast<uint8>((favors & 0x0000ff00) >> 8)),
    FavorOfZiying(static_cast<uint8>(favors & 0x000000ff)),
    InitMagicPoint(initMagicPoint)
{
}

void IRoleProperty::SetRoleFavor(ERole role, uint8 value)
{
    switch (role)
    {
    case ERole::Tianhe: FavorOfTianhe = value; break;

    case ERole::Lingsha: FavorOfLingsha = value; break;

    case ERole::Mengli: FavorOfMengli = value; break;

    case ERole::Ziying: FavorOfZiying = value; break;
    }
}

void IRoleProperty::AddRoleFavor(ERole role, uint8 value)
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

uint8 IRoleProperty::GetRoleFavor(ERole role) const
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
