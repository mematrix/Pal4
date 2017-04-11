#pragma once

#include <Platform.h>

#include "Util/MacroUtil.h"


/**
 * һ�ζ���������ģ�ͻ��ࡣ�洢һ�ι���/����������������ݣ����ݹ���/�������Ͳ�ͬ�����໯��Ӧ��ģ����
 */
struct PAL4_API FBaseAttackModel
{
    explicit FBaseAttackModel(int32 totalValue = 0) : TotalValue(totalValue) { }
    virtual ~FBaseAttackModel() = default;

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FBaseAttackModel)

    // ��ֵ���˺�ֵ���߻ָ�ֵ
    int32 TotalValue;
};
