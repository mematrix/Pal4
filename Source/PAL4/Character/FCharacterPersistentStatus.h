// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Util/FlagBitUtil.h"
#include "Core/ValueTransformer.h"
#include "Helper/FInfoModelAccessHelper.h"
#include "Model/ECharacterPropertyType.h"
#include "Model/FCharacterInfoModel.h"

template ValueTransformer<void*, ECharacterPropertyType, int32, int32>;
typedef ValueTransformer<void*, ECharacterPropertyType, int32, int32> FPersistentTransformer;


/**
 * 用于存储持久化的状态信息，比如装备、被动技能带来的状态信息
 */
class PAL4_API FCharacterPersistentStatus
{
public:
    typedef std::function<int32(void*, ECharacterPropertyType, int32)> FTransformAction;

    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterPropertyType::PropertyEnd \endcode，
     * 则说明有多个属性发生了变化。
     */
    DECLARE_EVENT_TwoParams(FCharacterPersistentStatus, FOnPropertyChangedEvent, const FCharacterPersistentStatus&, ECharacterPropertyType)

public:
    explicit FCharacterPersistentStatus(FInfoModelAccessHelper& base);
    FCharacterPersistentStatus(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus(FCharacterPersistentStatus&&) = default;

    FCharacterPersistentStatus& operator=(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus& operator=(FCharacterPersistentStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }

    int32 GetPropertyValue(ECharacterPropertyType type) const { return PersistentInfoAccessor.GetPropertyValue(type); }
    const FCharacterInfoModel& GetAccumulateInfo() const { return InfoModel; }

    void UpdatePropertyValue(ECharacterPropertyType type) const;
    void UpdateAllProperties() const;

    void AddTransformer(void*, ECharacterPropertyType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterPropertyType type);

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;

    FCharacterInfoModel InfoModel;

    FInfoModelAccessHelper BaseInfoAccessor;
    FInfoModelAccessHelper PersistentInfoAccessor;

    FPersistentTransformer Transformer;
};



template<typename... T>
class PAL4_API FCharacterStatusInfo
{
public:
    int32 GetStatusValue(ECharacterStatus status) const
    {
        switch (status)
        {
        case ECharacterStatus::Property:
        {
            int32 ret = 0;
            uint32 mask = 1;
            for (int32 i = 0; i < CharacterPropertyEnumCount; ++i)
            {
                if (propertyTransformers[i].Num() > 0)
                {
                    ret |= mask;
                }
                mask <<= 1;
            }
            return ret;
        }

        case ECharacterStatus::CommonBuff:
            return static_cast<int32>(CommonBuff);

        case ECharacterStatus::Invisible:
            return static_cast<int32>(IsInvisible);

        case ECharacterStatus::CanRevive:
            return static_cast<int32>(CanRevive);

        case ECharacterStatus::Poison:
            return static_cast<int32>(Poison);

        case ECharacterStatus::ControlledDebuff:
            return static_cast<int32>(ControlledDebuff);
            
        default:
            return 0;
        }
    }
};
