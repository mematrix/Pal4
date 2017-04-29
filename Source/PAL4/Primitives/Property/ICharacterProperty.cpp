// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "Util/EventUtil.h"
#include "ICharacterProperty.h"


ICharacterProperty::ICharacterProperty(int32 id, const FName& name, ERace race, EPhysicalAttackType type, EPhysicalAttackTarget target) :
    BasicInfo(id, name, race, type, target),
    OnBasicInfoChangedEvent()
{
}

int32 ICharacterProperty::GetBasicInfo(ECharacterBasicType type) const
{
    switch (type)
    {
    case ECharacterBasicType::Level:
        return BasicInfo.Level;

    case ECharacterBasicType::Experience:
        return BasicInfo.Experience;

    case ECharacterBasicType::MaxHealth:
        return BasicInfo.MaxHealthPoint;

    case ECharacterBasicType::MaxMana:
        return BasicInfo.MaxManaPoint;

    case ECharacterBasicType::MaxCraft:
        return BasicInfo.MaxCraftPoint;

    case ECharacterBasicType::Health:
        return BasicInfo.HealthPoint;

    case ECharacterBasicType::Mana:
        return BasicInfo.ManaPoint;

    case ECharacterBasicType::Craft:
        return BasicInfo.CraftPoint;

    case ECharacterBasicType::WaterPoint:
        return BasicInfo.MagicPoints[0];

    case ECharacterBasicType::FirePoint:
        return BasicInfo.MagicPoints[1];

    case ECharacterBasicType::ThunderPoint:
        return BasicInfo.MagicPoints[2];

    case ECharacterBasicType::WindPoint:
        return BasicInfo.MagicPoints[3];

    case ECharacterBasicType::SoilPoint:
        return BasicInfo.MagicPoints[4];

    default: return 0;
    }
}

void ICharacterProperty::SetBasicInfo(ECharacterBasicType type, int32 value)
{
    int32 oldValue;

    switch (type)
    {
    case ECharacterBasicType::Level:
        oldValue = BasicInfo.Level;
        BasicInfo.Level = value;
        break;

    case ECharacterBasicType::Experience:
        oldValue = BasicInfo.Experience;
        BasicInfo.Experience = value;
        break;

    case ECharacterBasicType::MaxHealth:
        oldValue = BasicInfo.MaxHealthPoint;
        BasicInfo.MaxHealthPoint = value;
        break;

    case ECharacterBasicType::MaxMana:
        oldValue = BasicInfo.MaxManaPoint;
        BasicInfo.MaxManaPoint = value;
        break;

    case ECharacterBasicType::MaxCraft:
        oldValue = BasicInfo.MaxCraftPoint;
        BasicInfo.MaxCraftPoint = value;
        break;

    case ECharacterBasicType::Health:
        oldValue = BasicInfo.HealthPoint;
        BasicInfo.HealthPoint = value;
        break;

    case ECharacterBasicType::Mana:
        oldValue = BasicInfo.ManaPoint;
        BasicInfo.ManaPoint = value;
        break;

    case ECharacterBasicType::Craft:
        oldValue = BasicInfo.CraftPoint;
        BasicInfo.CraftPoint = value;
        break;

    case ECharacterBasicType::WaterPoint:
        oldValue = BasicInfo.MagicPoints[0];
        BasicInfo.MagicPoints[0] = static_cast<uint8>(value);
        value = BasicInfo.MagicPoints[0];
        break;

    case ECharacterBasicType::FirePoint:
        oldValue = BasicInfo.MagicPoints[1];
        BasicInfo.MagicPoints[1] = static_cast<uint8>(value);
        value = BasicInfo.MagicPoints[1];
        break;

    case ECharacterBasicType::ThunderPoint:
        oldValue = BasicInfo.MagicPoints[2];
        BasicInfo.MagicPoints[2] = static_cast<uint8>(value);
        value = BasicInfo.MagicPoints[2];
        break;

    case ECharacterBasicType::WindPoint:
        oldValue = BasicInfo.MagicPoints[3];
        BasicInfo.MagicPoints[3] = static_cast<uint8>(value);
        value = BasicInfo.MagicPoints[3];
        break;

    case ECharacterBasicType::SoilPoint:
        oldValue = BasicInfo.MagicPoints[4];
        BasicInfo.MagicPoints[4] = static_cast<uint8>(value);
        value = BasicInfo.MagicPoints[4];
        break;

    default: return;
    }

    if (oldValue != value)
    {
        InvokeEvent(OnBasicInfoChangedEvent, *this, type);
    }
}
