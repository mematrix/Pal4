// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Core/ValueTransformer.h"
#include "Helper/FStatusInfoAccessHelper.h"
#include "Model/ECharacterStatusType.h"
#include "Model/FCharacterStatusInfo.h"

template ValueTransformer<void*, ECharacterStatusType, int32, int32>;
typedef ValueTransformer<void*, ECharacterStatusType, int32, int32> FPersistentTransformer;


/**
 * 用于存储持久化的状态信息，比如装备、被动技能带来的状态信息
 */
class PAL4_API FCharacterPersistentStatus
{
public:
    typedef std::function<int32(void*, ECharacterStatusType, int32)> FTransformAction;

    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterStatusType::PropertyEnd \endcode，
     * 则说明有多个属性发生了变化。
     */
    DECLARE_EVENT_TwoParams(FCharacterPersistentStatus, FOnPropertyChangedEvent, const FCharacterPersistentStatus&, ECharacterStatusType)

public:
    explicit FCharacterPersistentStatus(const FStatusInfoAccessHelper& base);
    FCharacterPersistentStatus(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus(FCharacterPersistentStatus&&) = default;

    FCharacterPersistentStatus& operator=(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus& operator=(FCharacterPersistentStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }

    int32 GetPropertyValue(ECharacterStatusType type) const { return PersistentInfoAccessor.GetPropertyValue(type); }
    const FCharacterStatusInfo& GetAccumulateInfo() const { return InfoModel; }

    const FStatusInfoAccessHelper& GetBaseAccessor() const { return BaseInfoAccessor; }
    const FStatusInfoAccessHelper& GetPersistentAccessor() const { return PersistentInfoAccessor; }

    void UpdatePropertyValue(ECharacterStatusType type) const;
    void UpdateAllProperties() const;

    void AddTransformer(void*, ECharacterStatusType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterStatusType type);

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;

    FCharacterStatusInfo InfoModel;

    FStatusInfoAccessHelper BaseInfoAccessor;
    FStatusInfoAccessHelper PersistentInfoAccessor;

    FPersistentTransformer Transformer;
};
