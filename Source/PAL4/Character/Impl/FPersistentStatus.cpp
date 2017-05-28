// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FPersistentStatus.h"
#include "Primitives/Helper/FStatusInfoAccessHelper.h"


FPersistentStatus::FPersistentStatus(const FCharacterStatusInfo& info) :
    ICharacterStatus(),
    BaseInfo(info),
    InfoModel(info)
{
}

int32 FPersistentStatus::GetPropertyValue(ECharacterStatusType type) const
{
    return FStatusInfoReader(InfoModel).GetPropertyValue(type);
}

void FPersistentStatus::UpdatePropertyValue(ECharacterStatusType type)
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

void FPersistentStatus::UpdateAllProperties()
{
    // ���Ƚ�ֵ����Ϊ����ֵ��Ȼ���Դ�Ϊ�������м���
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
