#pragma once

#include "FBaseAttackModel.h"

struct PAL4_API FMagicAttackModel : FBaseAttackModel
{
    explicit FMagicAttackModel(int32 totalDamage = 0, int32 originalDamage = 0) :
        FBaseAttackModel(totalDamage),
        OriginalDamageValue(originalDamage)
    {
    }

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FMagicAttackModel)

    // 原始仙术伤害。实际伤害=原始伤害*(1-仙抗)
    int32 OriginalDamageValue;
};
