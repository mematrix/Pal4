// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>

#include "../ICharacterStatus.h"


/**
 * ���ڴ洢�־û���״̬��Ϣ������װ�����������ܴ�����״̬��Ϣ
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
