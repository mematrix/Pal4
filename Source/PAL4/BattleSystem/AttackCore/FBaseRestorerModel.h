#pragma once

#include <Platform.h>

#include "Util/MacroUtil.h"


/**
 * �ָ��Զ��������ݻ��ࡣ
 */
struct PAL4_API FBaseRestorerModel
{
    explicit FBaseRestorerModel(int32 healthValue = 0, int32 manaValue = 0) :
        HealthValue(healthValue),
        ManaValue(manaValue)
    {
    }

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FBaseRestorerModel)

    // �ָ�����ֵ
    int32 HealthValue;
    // �ָ���ֵ
    int32 ManaValue;
};
