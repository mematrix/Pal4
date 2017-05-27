// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "Util/EventUtil.h"
#include "FCharacterTemporaryStatus.h"
#include "Primitives/Helper/FStatusInfoAccessHelper.h"


FCharacterTemporaryStatus::FCharacterTemporaryStatus(const ICharacterStatusProperty& status) :
    ICharacterTempStatus(),
    PersistentStatus(status),
    InfoModel{ 0 },
    BattleStatus()
{
    PersistentStatus.OnPropertyChanged().AddRaw(this, &FCharacterTemporaryStatus::OnPersistentStatusChanged);
}

FCharacterTemporaryStatus::FCharacterTemporaryStatus(FCharacterTemporaryStatus &&other) noexcept :
    ICharacterTempStatus(MoveTemp(other)),
    PersistentStatus(other.PersistentStatus),
    InfoModel(MoveTemp(other.InfoModel)),
    BattleStatus(other.BattleStatus)
{
    other.PersistentStatus.OnPropertyChanged().RemoveAll(&other);
    PersistentStatus.OnPropertyChanged().AddRaw(this, &FCharacterTemporaryStatus::OnPersistentStatusChanged);
}

FCharacterTemporaryStatus::~FCharacterTemporaryStatus()
{
    PersistentStatus.OnPropertyChanged().RemoveAll(this);
}

int32 FCharacterTemporaryStatus::GetPropertyValue(ECharacterStatusType type) const
{
    return FStatusInfoReader(InfoModel).GetPropertyValue(type);
}

void FCharacterTemporaryStatus::UpdatePropertyValue(ECharacterStatusType type)
{
    if (type >= ECharacterStatusType::PropertyEnd)
    {
        UpdateAllProperties();
    }
    else
    {
        auto persistent = FStatusInfoReader(PersistentStatus.GetAccumulatedInfo()).GetPropertyValue(type);
        auto value = Transformer.AccumulateByGroup(persistent, type, persistent);
        FStatusInfoAccessHelper(InfoModel).SetPropertyValue(type, value);

        NotifyPropertyChanged(type);
    }
}

void FCharacterTemporaryStatus::UpdateAllProperties()
{
    // 首先将值更新为持久化值，然后以此为基础进行计算
    InfoModel = PersistentStatus.GetAccumulatedInfo();
    FStatusInfoReader persistentInfo(PersistentStatus.GetAccumulatedInfo());
    FStatusInfoAccessHelper infoAccessor(InfoModel);
    Transformer.Traverse([&persistentInfo, &infoAccessor](int32 key, ECharacterStatusType type, const FTransformAction& func)
    {
        auto persistent = persistentInfo.GetPropertyValue(type);
        auto value = infoAccessor.GetPropertyValue(type);
        value += func(persistent);
        infoAccessor.SetPropertyValue(type, value);
    });

    NotifyPropertyChanged(ECharacterStatusType::PropertyEnd);
}

void FCharacterTemporaryStatus::OnCombatStatusChanged(ECombatStatus status) const
{
    if (status == ECombatStatus::Property || status > ECombatStatus::Debuff)
    {
        return;
    }

    NotifyCombatStatusChanged(status);
}

void FCharacterTemporaryStatus::OnPersistentStatusChanged(const ICharacterStatusProperty&, ECharacterStatusType type)
{
    UpdatePropertyValue(type);
}
