// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <SharedPointer.h>

#include "Primitives/Property/ICharacterProperty.h"
#include "Primitives/EnumType/ERole.h"
#include "FCharacterPersistentStatus.h"

/**
 * 主角属性对象
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
    // 人物固有属性信息（包括ID、名称、种族、普攻类型等）
    TSharedRef<FCharacterInherentInfo> InherentInfo;
    // 人物自身属性信息。和等级绑定
    FCharacterStatusInfo StatusInfo;
    // 人物属性对象。计算了状态加成（装备等）之后的值
    FCharacterPersistentStatus PersistentStatus;

    // 对天河好感度
    int32 FavorOfTianhe;
    // 对菱纱好感度
    int32 FavorOfLingsha;
    // 对梦璃好感度
    int32 FavorOfMengli;
    // 对紫英好感度
    int32 FavorOfZiying;
};
