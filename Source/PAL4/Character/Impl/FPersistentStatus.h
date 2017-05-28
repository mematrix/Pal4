// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>

#include "../ICharacterStatus.h"


/**
 * 用于存储持久化的状态信息，比如装备、被动技能带来的状态信息
 */
class PAL4_API FPersistentStatus : public ICharacterStatus
{
public:
    explicit FPersistentStatus(const FCharacterStatusInfo&);
    FPersistentStatus(const FPersistentStatus&) = delete;
    FPersistentStatus(FPersistentStatus&&) = default;

    FPersistentStatus& operator=(const FPersistentStatus&) = delete;
    FPersistentStatus& operator=(FPersistentStatus&&) = default;

    int32 GetPropertyValue(ECharacterStatusType type) const override;
    const FCharacterStatusInfo& GetAccumulatedInfo() const override { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) override;
    void UpdateAllProperties() override;

private:
    const FCharacterStatusInfo& BaseInfo;
    FCharacterStatusInfo InfoModel;
};
