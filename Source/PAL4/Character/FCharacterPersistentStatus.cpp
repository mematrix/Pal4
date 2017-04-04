// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "Util/EventUtil.h"
#include "FCharacterPersistentStatus.h"

FCharacterPersistentStatus::FCharacterPersistentStatus(FInfoModelAccessHelper& base) :
    OnPropertyChangedEvent(),
    InfoModel(),
    BaseInfoAccessor(base),
    PersistentInfoAccessor(InfoModel),
    Transformer()
{
}

void FCharacterPersistentStatus::UpdatePropertyValue(ECharacterPropertyType type) const
{
    if (type >= ECharacterPropertyType::PropertyEnd)
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
    // ���Ƚ�ֵ����Ϊ����ֵ��Ȼ���Դ�Ϊ�������м���
    PersistentInfoAccessor.GetModel() = BaseInfoAccessor.GetModel();
    Transformer.Traverse([this](void* key, ECharacterPropertyType type, const FTransformAction& func)
    {
        auto base = BaseInfoAccessor.GetPropertyValue(type);
        auto value = PersistentInfoAccessor.GetPropertyValue(type);
        value += func(key, type, base);
        PersistentInfoAccessor.SetPropertyValue(type, value);
    });

    InvokeEvent(OnPropertyChangedEvent, *this, ECharacterPropertyType::PropertyEnd);
}

void FCharacterPersistentStatus::AddTransformer(void* key, ECharacterPropertyType type, const FTransformAction& func)
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    Transformer.AddTransformer(key, type, func);
    UpdatePropertyValue(type);
}

void FCharacterPersistentStatus::RemoveTransformer(void* key, ECharacterPropertyType type)
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    Transformer.RemoveTransformer(key, type);
    UpdatePropertyValue(type);
}

