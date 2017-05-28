// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "Util/EventUtil.h"
#include "FTemporaryStatus.h"
#include "Primitives/Helper/FStatusInfoAccessHelper.h"


FTemporaryStatus::FTemporaryStatus(const ICharacterStatus& status) :
    ITemporaryStatus(),
    PersistentStatus(status),
    InfoModel(status.GetAccumulatedInfo())
{
    PersistentStatus.OnPropertyChanged().AddRaw(this, &FTemporaryStatus::OnPersistentStatusChanged);
}

FTemporaryStatus::FTemporaryStatus(FTemporaryStatus &&other) noexcept :
    ITemporaryStatus(MoveTemp(other)),
    PersistentStatus(other.PersistentStatus),
    InfoModel(MoveTemp(other.InfoModel))
{
    //other.PersistentStatus.OnPropertyChanged().RemoveAll(&other);
    PersistentStatus.OnPropertyChanged().AddRaw(this, &FTemporaryStatus::OnPersistentStatusChanged);
}

FTemporaryStatus::~FTemporaryStatus()
{
    PersistentStatus.OnPropertyChanged().RemoveAll(this);
}

int32 FTemporaryStatus::GetPropertyValue(ECharacterStatusType type) const
{
    return FStatusInfoReader(InfoModel).GetPropertyValue(type);
}

void FTemporaryStatus::UpdatePropertyValue(ECharacterStatusType type)
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

void FTemporaryStatus::UpdateAllProperties()
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

void FTemporaryStatus::OnCombatStatusChanged(ECombatStatus status) const
{
    if (status > ECombatStatus::Debuff)
    {
        return;
    }

    NotifyCombatStatusChanged(status);
}

void FTemporaryStatus::OnPersistentStatusChanged(const ICharacterStatus&, ECharacterStatusType type)
{
    UpdatePropertyValue(type);
}
