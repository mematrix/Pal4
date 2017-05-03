// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <SharedPointer.h>

#include "Primitives/Property/ICharacterProperty.h"
#include "Primitives/EnumType/ERole.h"
#include "FCharacterPersistentStatus.h"

/**
 * �������Զ���
 */
class PAL4_API FRoleProperty : public ICharacterProperty
{
public:
	FRoleProperty(const TSharedRef<FCharacterInherentInfo>&, const FCharacterStatusInfo&);

    void UpdateStatusInfo(ECharacterStatusType, int32) override;

    void UpdateStatusInfo(const FCharacterStatusInfo&) override;

    bool IsDebuffImmune(EImmune) const override final { return false; }

    const FCharacterInherentInfo& GetCharacterInherentInfo() const override final
    {
        return InherentInfo.Get();
    }

    FCharacterPersistentStatus& StatusProperty() override final { return PersistentStatus; }

    const FCharacterPersistentStatus& StatusProperty() const override final { return PersistentStatus; }

    void SetRoleFavor(ERole, int32);
    void AddRoleFavor(ERole, int32);
    int32 GetRoleFavor(ERole) const;

private:
    // �������������Ϣ������ID�����ơ����塢�չ����͵ȣ�
    TSharedRef<FCharacterInherentInfo> InherentInfo;
    // ��������������Ϣ���͵ȼ���
    FCharacterStatusInfo StatusInfo;
    // �������Զ��󡣼�����״̬�ӳɣ�װ���ȣ�֮���ֵ
    FCharacterPersistentStatus PersistentStatus;

    // ����Ӻøж�
    int32 FavorOfTianhe;
    // ����ɴ�øж�
    int32 FavorOfLingsha;
    // �������øж�
    int32 FavorOfMengli;
    // ����Ӣ�øж�
    int32 FavorOfZiying;
};
