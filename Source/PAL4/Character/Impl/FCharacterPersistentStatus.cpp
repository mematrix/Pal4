// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterPersistentStatus.h"
#include "Primitives/Helper/FStatusInfoAccessHelper.h"


FCharacterPersistentStatus::FCharacterPersistentStatus(const FCharacterStatusInfo& info) :
    ICharacterStatusProperty(),
    BaseInfo(info),
    InfoModel(info)
{
}

int32 FCharacterPersistentStatus::GetPropertyValue(ECharacterStatusType type) const
{
    return FStatusInfoReader(InfoModel).GetPropertyValue(type);
}

void FCharacterPersistentStatus::UpdatePropertyValue(ECharacterStatusType type)
{
    if (type >= ECharacterStatusType::PropertyEnd)
    {
        UpdateAllProperties();
    }
    else
    {
        auto base = FStatusInfoReader(BaseInfo).GetPropertyValue(type);
        auto value = Transformer.AccumulateByGroup(base, type, base);
        FStatusInfoAccessHelper(InfoModel).SetPropertyValue(type, value);

        NotifyPropertyChanged(type);
    }
}

void FCharacterPersistentStatus::UpdateAllProperties()
{
    // 首先将值更新为基础值，然后以此为基础进行计算
    InfoModel = BaseInfo;
    FStatusInfoReader baseInfoReader(BaseInfo);
    FStatusInfoAccessHelper infoAccessor(InfoModel);
    Transformer.Traverse([&baseInfoReader, &infoAccessor](int32 key, ECharacterStatusType type, const FTransformAction& func)
    {
        auto base = baseInfoReader.GetPropertyValue(type);
        auto value = infoAccessor.GetPropertyValue(type);
        value += func(base);
        infoAccessor.SetPropertyValue(type, value);
    });

    NotifyPropertyChanged(ECharacterStatusType::PropertyEnd);
}
