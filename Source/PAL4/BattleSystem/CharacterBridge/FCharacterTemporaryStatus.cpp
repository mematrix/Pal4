// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "Util/EventUtil.h"
#include "FCharacterTemporaryStatus.h"

FCharacterTemporaryStatus::FCharacterTemporaryStatus(FCharacterPersistentStatus& status) :
    OnPropertyChangedEvent(),
    OnBattleStatusChangedEvent(),
    InfoModel{0},
    PersistentStatus(status),
    BaseInfoAccessor(status.GetBaseAccessor()),
    PersistentInfoAccessor(status.GetPersistentAccessor()),
    TemporaryInfoAccessor(InfoModel),
    Transformer(),
    CommonBuff(ECommonBuff::None),
    Poison(EPoison::None),
    ControlledDebuff(EControlledDebuff::None),
    IsInvisible(false),
    CanRevive(false)
{
    PersistentStatus.OnPropertyChanged().AddRaw(this, &FCharacterTemporaryStatus::OnPersistentStatusChanged);
}

FCharacterTemporaryStatus::~FCharacterTemporaryStatus()
{
    PersistentStatus.OnPropertyChanged().RemoveAll(this);
}

void FCharacterTemporaryStatus::UpdatePropertyValue(ECharacterStatusPropertyType type) const
{
    if (type >= ECharacterStatusPropertyType::PropertyEnd)
    {
        UpdateAllProperties();
    }
    else
    {
        auto base = BaseInfoAccessor.GetPropertyValue(type);
        auto persistent = PersistentInfoAccessor.GetPropertyValue(type);
        auto value = Transformer.AccumulateByGroup(persistent, type, base, persistent);
        TemporaryInfoAccessor.SetPropertyValue(type, value);

        InvokeEvent(OnPropertyChangedEvent, *this, type);
    }
}

void FCharacterTemporaryStatus::UpdateAllProperties() const
{
    // 首先将值更新为持久化值，然后以此为基础进行计算
    TemporaryInfoAccessor.GetModel() = PersistentInfoAccessor.GetModel();
    Transformer.Traverse([this](void* key, ECharacterStatusPropertyType type, const FTransformAction& func)
    {
        auto base = BaseInfoAccessor.GetPropertyValue(type);
        auto persistent = PersistentInfoAccessor.GetPropertyValue(type);
        auto value = TemporaryInfoAccessor.GetPropertyValue(type);
        value += func(key, type, base, persistent);
        TemporaryInfoAccessor.SetPropertyValue(type, value);
    });

    InvokeEvent(OnPropertyChangedEvent, *this, ECharacterStatusPropertyType::PropertyEnd);
}

void FCharacterTemporaryStatus::AddTransformer(void* key, ECharacterStatusPropertyType type, const FTransformAction& func)
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    Transformer.AddTransformer(key, type, func);
    UpdatePropertyValue(type);
}

void FCharacterTemporaryStatus::RemoveTransformer(void* key, ECharacterStatusPropertyType type)
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    Transformer.RemoveTransformer(key, type);
    UpdatePropertyValue(type);
}

void FCharacterTemporaryStatus::NotifyBattleStatusChanged(ECharacterBattleStatus status)
{
    if (status == ECharacterBattleStatus::Property || status > ECharacterBattleStatus::ControlledDebuff)
    {
        return;
    }

    InvokeEvent(OnBattleStatusChangedEvent, *this, status);
}

void FCharacterTemporaryStatus::OnPersistentStatusChanged(const FCharacterPersistentStatus&, ECharacterStatusPropertyType type) const
{
    UpdatePropertyValue(type);
}
