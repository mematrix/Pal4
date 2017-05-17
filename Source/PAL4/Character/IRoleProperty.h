#pragma once

#include "ICharacterProperty.h"
#include "Primitives/EnumType/ERole.h"


/**
 * 主角属性基类
 */
class PAL4_API IRoleProperty : public ICharacterProperty
{
protected:
    IRoleProperty(const FCharacterBasicInfo&, uint32, uint8 initMagicPoint);
    IRoleProperty(const IRoleProperty&) = default;
    IRoleProperty(IRoleProperty&&) = default;

    IRoleProperty& operator=(const IRoleProperty&) = default;
    IRoleProperty& operator=(IRoleProperty&&) = default;

public:
    bool IsDebuffImmune(EImmune) const override final { return false; }

    void SetRoleFavor(ERole, uint8);

    void AddRoleFavor(ERole, uint8);

    uint8 GetRoleFavor(ERole) const;

    uint8 GetInitMagicPoint() const { return InitMagicPoint; }

private:
    // 对天河好感度
    uint8 FavorOfTianhe;
    // 对菱纱好感度
    uint8 FavorOfLingsha;
    // 对梦璃好感度
    uint8 FavorOfMengli;
    // 对紫英好感度
    uint8 FavorOfZiying;
    // 初始仙灵点数（即0级仙灵点数，角色当前仙灵点总数=等级+初始仙灵点数）
    uint8 InitMagicPoint;
};
