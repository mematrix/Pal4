#pragma once

#include "ICharacterProperty.h"
#include "../EnumType/ERole.h"


/**
 * 主角属性基类
 */
class PAL4_API IRoleProperty : public ICharacterProperty
{
protected:
    IRoleProperty(const FCharacterBasicInfo&, int32[4]);
    IRoleProperty(const IRoleProperty&) = default;
    IRoleProperty(IRoleProperty&&) = default;

    IRoleProperty& operator=(const IRoleProperty&) = default;
    IRoleProperty& operator=(IRoleProperty&&) = default;

public:
    bool IsDebuffImmune(EImmune) const override final { return false; }

    void SetRoleFavor(ERole, int32);

    void AddRoleFavor(ERole, int32);

    int32 GetRoleFavor(ERole) const;

private:
    // 对天河好感度
    int32 FavorOfTianhe;
    // 对菱纱好感度
    int32 FavorOfLingsha;
    // 对梦璃好感度
    int32 FavorOfMengli;
    // 对紫英好感度
    int32 FavorOfZiying;
};
