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

class PAL4_API FCharacterPersistentStatus
{
public:
    typedef std::function<int32(void*, ECharacterPropertyType, int32)> FTransformAction;

    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterPropertyType::PropertyEnd，
     * 则说明有多个属性发生了变化。
     */
    DECLARE_EVENT_TwoParams(FCharacterPersistentStatus, FOnPropertyChangedEvent, const FCharacterPersistentStatus&, ECharacterPropertyType)

public:
    explicit FCharacterPersistentStatus(FInfoModelAccessHelper& base);
    FCharacterPersistentStatus(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus(FCharacterPersistentStatus&&) = default;

    FCharacterPersistentStatus& operator=(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus& operator=(FCharacterPersistentStatus&&) = default;

private:
    FCharacterInfoModel InfoModel;

    FInfoModelAccessHelper BaseInfoAccessor;
    FInfoModelAccessHelper PersistentInfoAccessor;

    FPersistentTransformer Transformer;
};


template<typename... T>
class PAL4_API FCharacterPropertyStatus;

/**
 *
 */
template<typename... T>
class PAL4_API FCharacterStatusInfo
{
    friend class FCharacterPropertyStatus<T...>;

public:
    FCharacterStatusInfo() = default;
    FCharacterStatusInfo(FCharacterStatusInfo&&) = default;
    FCharacterStatusInfo(const FCharacterStatusInfo&) = delete;
    ~FCharacterStatusInfo() = default;

    FCharacterStatusInfo& operator= (FCharacterStatusInfo&&) = default;
    FCharacterStatusInfo& operator= (const FCharacterStatusInfo&) = delete;

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

    const TMap<void*, int32(void*, ECharacterProperty, T...)>* GetPropertyTransformer(ECharacterProperty prop) const
    {
        switch (prop)
        {
        case ECharacterProperty::Attack:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Attack)];

        case ECharacterProperty::Luck:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Luck)];

        case ECharacterProperty::Nimbus:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Nimbus)];

        case ECharacterProperty::Speed:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Speed)];

        case ECharacterProperty::Defence:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Defence)];

        default:
            return nullptr;
        }
    }

private:
    void AddPropertyTransformer(uint32 props, const void* key, int32(*value)(void*, ECharacterProperty, T...))
    {
        for (int32 i = 0; i < CharacterPropertyEnumCount && props; ++i)
        {
            if (props & 0x01)
            {
                propertyTransformers[i].Add(key, value);
            }
            props >>= 1;
        }
    }

    void RemovePropertyTransformer(uint32 props, const void* key)
    {
        for (int32 i = 0; i < CharacterPropertyEnumCount && props; ++i)
        {
            if (props & 0x01)
            {
                propertyTransformers[i].Remove(key);
            }
            props >>= 1;
        }
    }

private:
    // 属性增益变换列表。存储了每一个可附加计算状态的属性的变换列表
    TMap<void*, int32(void*, ECharacterProperty, T...)> propertyTransformers[CharacterPropertyEnumCount];

    // Buff状态
    // 通用Buff：镜壁界宁
    ECommonBuff CommonBuff;
    // 中毒状态
    EPoison Poison;
    // 控制性Debuff
    EControlledDebuff ControlledDebuff;
    // 是否隐身状态
    bool IsInvisible;
    // 是否可在死亡后立即复活。“生”状态
    bool CanRevive;
};

// 用于存储持久化的状态信息，比如装备、被动技能带来的状态信息
using FPersistenceStatusInfo = FCharacterStatusInfo<int32>;
// 用于存储临时的状态信息，比如战斗中使用技能、仙术等附加的Buff
using FTemporaryStatusInfo = FCharacterStatusInfo<int32, int32>;
