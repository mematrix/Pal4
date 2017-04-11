#pragma once

#include <Platform.h>

#include "Util/MacroUtil.h"


/**
 * 恢复性动作的数据基类。
 */
struct PAL4_API FBaseRestorerModel
{
    explicit FBaseRestorerModel(int32 healthValue = 0, int32 manaValue = 0) :
        HealthValue(healthValue),
        ManaValue(manaValue)
    {
    }

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FBaseRestorerModel)

    // 恢复生命值
    int32 HealthValue;
    // 恢复神值
    int32 ManaValue;
};
