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
    // ��ͨ�����˺�ֵ
    int32 AttackDamageValue;
    // ֱ�������˺�ֵ
    int32 DirectDamageValue;
    // Ԫ���˺�ֵ
    int32 ElementalDamageValue;
};
