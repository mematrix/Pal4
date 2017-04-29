// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>

#include "Core/ValueTransformer.h"
#include "Primitives/Property/ICharacterStatusProperty.h"
#include "Primitives/Helper/FStatusInfoAccessHelper.h"

template ValueTransformer<void*, ECharacterStatusType, int32, int32>;
typedef ValueTransformer<void*, ECharacterStatusType, int32, int32> FPersistentTransformer;


/**
 * 用于存储持久化的状态信息，比如装备、被动技能带来的状态信息
 */
class PAL4_API FCharacterPersistentStatus : ICharacterStatusProperty
{
public:
    typedef std::function<int32(void*, ECharacterStatusType, int32)> FTransformAction;

public:
    explicit FCharacterPersistentStatus(const FCharacterStatusInfo& base);
    FCharacterPersistentStatus(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus(FCharacterPersistentStatus&&) = default;

    FCharacterPersistentStatus& operator=(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus& operator=(FCharacterPersistentStatus&&) = default;

    int32 GetPropertyValue(ECharacterStatusType type) const override { return PersistentInfoAccessor.GetPropertyValue(type); }
    const FCharacterStatusInfo& GetAccumulateInfo() const override { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) const override;
    void UpdateAllProperties() const override;

    void AddTransformer(void*, ECharacterStatusType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterStatusType type);

private:
    FCharacterStatusInfo InfoModel;

    FStatusInfoReader BaseInfoReader;
    FStatusInfoAccessHelper PersistentInfoAccessor;

    FPersistentTransformer Transformer;
};
