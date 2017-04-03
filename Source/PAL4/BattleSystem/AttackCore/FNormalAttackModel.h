#pragma once

#include <Platform.h>

#include "FBaseAttackModel.h"

class PAL4_API FNormalAttackModel : public FBaseAttackModel
{
public:
    int32 GetAttackDamageValue() const { return AttackDamageValue; }
    int32 GetDirectDamageValue() const { return DirectDamageValue; }
    int32 GetElementalDamageValue() const { return ElementalDamageValue; }

private:
    // 普通武力伤害值
    int32 AttackDamageValue;
    // 直接物理伤害值
    int32 DirectDamageValue;
    // 元素伤害值
    int32 ElementalDamageValue;
};
