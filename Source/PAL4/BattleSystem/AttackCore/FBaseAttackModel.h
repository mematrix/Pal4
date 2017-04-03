#pragma once

/**
 * 攻击数据模型基类。存储一次攻击的所有相关数据，根据攻击类型不同，子类化对应的模型类
 * @warning 不被设计为多态，仅为数据结构设计。继承请考虑使用private或者protected继承
 */
class PAL4_API FBaseAttackModel
{
protected:
    FBaseAttackModel() = default;
    FBaseAttackModel(const FBaseAttackModel&) = default;
    FBaseAttackModel& operator=(const FBaseAttackModel&) = default;

    ~FBaseAttackModel() = default;
};
