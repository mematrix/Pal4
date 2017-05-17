// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <SharedPointer.h>

#include "../IRoleProperty.h"
#include "FCharacterPersistentStatus.h"


/**
 * 主角属性对象
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
    // 人物固有属性信息（包括ID、名称、种族、普攻类型等）
    TSharedRef<FCharacterInherentInfo> InherentInfo;
    // 人物自身属性信息。和等级绑定
    FCharacterStatusInfo StatusInfo;
    // 人物属性对象。计算了状态加成（装备等）之后的值
    FCharacterPersistentStatus PersistentStatus;
};
