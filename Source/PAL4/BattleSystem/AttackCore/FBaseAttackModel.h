#pragma once

#include <Platform.h>

/**
 * 攻击数据模型基类。存储一次攻击的所有相关数据，根据攻击类型不同，子类化对应的模型类
 */
class PAL4_API FBaseAttackModel
{
protected:
    explicit FBaseAttackModel(int32 totalDamageValue = 0) : TotalDamageValue(totalDamageValue) { }
    FBaseAttackModel(const FBaseAttackModel&) = default;
    FBaseAttackModel& operator=(const FBaseAttackModel&) = default;

    virtual ~FBaseAttackModel() = default;

public:
    int32 GetTotalDamageValue() const { return TotalDamageValue; }

protected:
    int32 TotalDamageValue;
};
