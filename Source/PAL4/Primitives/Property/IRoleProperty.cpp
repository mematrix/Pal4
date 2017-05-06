// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "IRoleProperty.h"

IRoleProperty::IRoleProperty(const FCharacterBasicInfo& info, int32 favors[4]) :
    ICharacterProperty(info),
    FavorOfTianhe(favors[0]),
    FavorOfLingsha(favors[1]),
    FavorOfMengli(favors[2]),
    FavorOfZiying(favors[3])
{
}
