#pragma once

#include <Platform.h>

#define MAKE_DEFAULT_COPY_CTOR_AND_OP(ClassName) \
    ClassName(const ClassName&) = default; \
    ClassName& operator=(const ClassName&) = default;


/**
 * 攻击数据模型基类。存储一次攻击的所有相关数据，根据攻击类型不同，子类化对应的模型类
 */
struct PAL4_API FBaseAttackModel
{
    explicit FBaseAttackModel(int32 totalDamage = 0) : TotalDamageValue(totalDamage) { }
    virtual ~FBaseAttackModel() = default;

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FBaseAttackModel)

    int32 TotalDamageValue;
};
