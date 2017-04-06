// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "Util/EventUtil.h"
#include "FCharacterPersistentStatus.h"

FCharacterPersistentStatus::FCharacterPersistentStatus(FStatusInfoAccessHelper& base) :
    OnPropertyChangedEvent(),
    InfoModel(),
    BaseInfoAccessor(base),
    PersistentInfoAccessor(InfoModel),
    Transformer()
{
}

void FCharacterPersistentStatus::UpdatePropertyValue(ECharacterStatusPropertyType type) const
{
    if (type >= ECharacterStatusPropertyType::PropertyEnd)
    {
        UpdateAllProperties();
    }
    else
    {
        auto base = BaseInfoAccessor.GetPropertyValue(type);
        auto value = Transformer.AccumulateByGroup(base, type, base);
        PersistentInfoAccessor.SetPropertyValue(type, value);

        InvokeEvent(OnPropertyChangedEvent, *this, type);
    }
}

void FCharacterPersistentStatus::UpdateAllProperties() const
{
    // 首先将值更新为基础值，然后以此为基础进行计算
    PersistentInfoAccessor.GetModel() = BaseInfoAccessor.GetModel();
    Transformer.Traverse([this](void* key, ECharacterStatusPropertyType type, const FTransformAction& func)
    {
        auto base = BaseInfoAccessor.GetPropertyValue(type);
        auto value = PersistentInfoAccessor.GetPropertyValue(type);
        value += func(key, type, base);
        PersistentInfoAccessor.SetPropertyValue(type, value);
    });

    InvokeEvent(OnPropertyChangedEvent, *this, ECharacterStatusPropertyType::PropertyEnd);
}

void FCharacterPersistentStatus::AddTransformer(void* key, ECharacterStatusPropertyType type, const FTransformAction& func)
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    Transformer.AddTransformer(key, type, func);
    UpdatePropertyValue(type);
}

void FCharacterPersistentStatus::RemoveTransformer(void* key, ECharacterStatusPropertyType type)
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    Transformer.RemoveTransformer(key, type);
    UpdatePropertyValue(type);
}

