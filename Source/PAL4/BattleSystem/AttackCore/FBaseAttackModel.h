#pragma once

#include <Platform.h>

/**
 * ��������ģ�ͻ��ࡣ�洢һ�ι���������������ݣ����ݹ������Ͳ�ͬ�����໯��Ӧ��ģ����
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
