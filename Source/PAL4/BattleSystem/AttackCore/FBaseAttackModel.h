#pragma once

#include <Platform.h>

#include "Util/MacroUtil.h"


/**
 * 一次动作的数据模型基类。存储一次攻击/辅助的所有相关数据，根据攻击/辅助类型不同，子类化对应的模型类
 */
struct PAL4_API FBaseAttackModel
{
    explicit FBaseAttackModel(int32 totalValue = 0) : TotalValue(totalValue) { }
    virtual ~FBaseAttackModel() = default;

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FBaseAttackModel)

    // 总值。伤害值或者恢复值
    int32 TotalValue;
};
