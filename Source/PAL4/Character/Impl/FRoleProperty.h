// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <SharedPointer.h>

#include "../IRoleProperty.h"
#include "FCharacterPersistentStatus.h"


/**
 * �������Զ���
 */
class PAL4_API FRoleProperty : public IRoleProperty
{
public:
	FRoleProperty(const TSharedRef<FCharacterInherentInfo>&, const FCharacterBasicInfo&, const FCharacterStatusInfo&, int32[4], int32);
    FRoleProperty(const FRoleProperty&) = default;
    FRoleProperty(FRoleProperty&&) = default;

    FRoleProperty& operator=(const FRoleProperty&) = default;
    FRoleProperty& operator=(FRoleProperty&&) = default;

    void UpdateStatusInfo(ECharacterStatusType, int32) override final;

    void UpdateStatusInfo(const FCharacterStatusInfo&) override final;

    const FCharacterInherentInfo& GetCharacterInherentInfo() const override final
    {
        return InherentInfo.Get();
    }

    FCharacterPersistentStatus& StatusProperty() override final { return PersistentStatus; }

    const FCharacterPersistentStatus& StatusProperty() const override final { return PersistentStatus; }

private:
    // �������������Ϣ������ID�����ơ����塢�չ����͵ȣ�
    TSharedRef<FCharacterInherentInfo> InherentInfo;
    // ��������������Ϣ���͵ȼ���
    FCharacterStatusInfo StatusInfo;
    // �������Զ��󡣼�����״̬�ӳɣ�װ���ȣ�֮���ֵ
    FCharacterPersistentStatus PersistentStatus;
};
