#pragma once

#include <Platform.h>

#define MAKE_DEFAULT_COPY_CTOR_AND_OP(ClassName) \
    ClassName(const ClassName&) = default; \
    ClassName& operator=(const ClassName&) = default;


/**
 * ��������ģ�ͻ��ࡣ�洢һ�ι���������������ݣ����ݹ������Ͳ�ͬ�����໯��Ӧ��ģ����
 */
struct PAL4_API FBaseAttackModel
{
    explicit FBaseAttackModel(int32 totalDamage = 0) : TotalDamageValue(totalDamage) { }
    virtual ~FBaseAttackModel() = default;

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FBaseAttackModel)

    int32 TotalDamageValue;
};
