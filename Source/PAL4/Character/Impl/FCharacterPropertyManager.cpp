// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterPropertyManager.h"
#include "Util/EventUtil.h"


FCharacterPropertyManager::FCharacterPropertyManager(FCharacterBasicInfo& info) :
    ICharacterPropertyManager(),
    BasicInfo(info)
{
}

int32 FCharacterPropertyManager::AddHealthValue(int32 value)
{
    auto old = BasicInfo.HealthPoint;
    auto temp = BasicInfo.HealthPoint + value;
    BasicInfo.HealthPoint = temp > BasicInfo.MaxHealthPoint ? BasicInfo.MaxHealthPoint : (temp < 0 ? 0 : temp);

    if (BasicInfo.HealthPoint - old != 0)
    {
        InvokeEvent(OnPropertyChangedEvent, *this, ECharacterBasicType::Health);
        if (!old) // old == 0，说明人物复活
        {
            InvokeEvent(OnCharacterReviveEvent, *this);
        }
        if (!BasicInfo.HealthPoint) // HealthPoint == 0，说明角色死亡
        {
            InvokeEvent(OnCharacterDeadEvent, *this);
        }
    }

    return BasicInfo.HealthPoint - old;
}

int32 FCharacterPropertyManager::AddManaValue(int32 value)
{
    auto old = BasicInfo.ManaPoint;
    auto temp = BasicInfo.ManaPoint + value;
    BasicInfo.ManaPoint = temp > BasicInfo.MaxManaPoint ? BasicInfo.MaxManaPoint : (temp < 0 ? 0 : temp);

    if (BasicInfo.ManaPoint - old != 0)
    {
        InvokeEvent(OnPropertyChangedEvent, *this, ECharacterBasicType::Mana);
    }

    return BasicInfo.ManaPoint - old;
}

int32 FCharacterPropertyManager::AddCraftValue(int32 value)
{
    auto old = BasicInfo.CraftPoint;
    auto temp = BasicInfo.CraftPoint + value;
    BasicInfo.CraftPoint = temp > BasicInfo.MaxCraftPoint ? BasicInfo.MaxCraftPoint : (temp < 0 ? 0 : temp);

    if (BasicInfo.CraftPoint - old != 0)
    {
        InvokeEvent(OnPropertyChangedEvent, *this, ECharacterBasicType::Craft);
    }

    return BasicInfo.CraftPoint - old;
}
