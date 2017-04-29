// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>

#include "Primitives/Property/ICharacterStatusProperty.h"


/**
 * 用于存储持久化的状态信息，比如装备、被动技能带来的状态信息
 */
class PAL4_API FCharacterPersistentStatus : ICharacterStatusProperty
{
    using FStatusTransformer = ValueTransformer<void*, ECharacterStatusType, int32, int32>;

public:
    explicit FCharacterPersistentStatus(const FCharacterStatusInfo&);
    FCharacterPersistentStatus(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus(FCharacterPersistentStatus&&) = default;

    FCharacterPersistentStatus& operator=(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus& operator=(FCharacterPersistentStatus&&) = default;

    int32 GetPropertyValue(ECharacterStatusType type) const override;
    const FCharacterStatusInfo& GetAccumulatedInfo() const override { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) override;
    void UpdateAllProperties() override;

private:
    const FCharacterStatusInfo& BaseInfo;
    FCharacterStatusInfo InfoModel;
};
