// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/Interface/Character/ICharacterPropertyManager.h"
#include "Primitives/Model/FCharacterBasicInfo.h"
#include "Primitives/EnumType/ECharacterBasicType.h"


/**
 * 
 */
class PAL4_API FCharacterPropertyManager : public ICharacterPropertyManager
{
public:
    explicit FCharacterPropertyManager(FCharacterBasicInfo&);
    FCharacterPropertyManager(const FCharacterPropertyManager&) = default;
    FCharacterPropertyManager(FCharacterPropertyManager&&) = default;

    bool IsPlayer() const override { return BasicInfo.IsPlayer; }

    bool IsAlive() const override { return 0 != BasicInfo.HealthPoint; }

    int32 GetId() const override { return BasicInfo.ID; }

    int32 GetHealthValue() const override { return BasicInfo.HealthPoint; }

    int32 GetManaValue() const override { return BasicInfo.ManaPoint; }

    int32 GetCraftValue() const override { return BasicInfo.CraftPoint; }

    int32 AddHealthValue(int32) override;

    int32 AddManaValue(int32) override;

    int32 AddCraftValue(int32) override;

    int32 GetMagicPoint(EMagicCategory category) override { return BasicInfo.MagicPoints[static_cast<int32>(category)]; }

private:
    FCharacterBasicInfo& BasicInfo;
};
