#pragma once

#include "FBaseAttackModel.h"


/**
 * 特技伤害
 */
struct PAL4_API FSkillAttackModel : FBaseAttackModel
{
    explicit FSkillAttackModel(int32 totalDamage = 0, int32 baseDamage = 0, int32 fixedDamage = 0) :
        FBaseAttackModel(totalDamage),
        BaseDamageValue(baseDamage),
        FixedDamageValue(fixedDamage)
    {
    }

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FSkillAttackModel)

    // 武力值计算出来的伤害值，不包括物抗减伤。对于攻击多次的技能，值为单次攻击结果
    int32 BaseDamageValue;
    // 固定伤害，和被攻击者直接物理伤害值有关
    int32 FixedDamageValue;
};
