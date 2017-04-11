#pragma once

#include "FBaseAttackModel.h"


/**
 * �ؼ��˺�
 */
struct PAL4_API FSkillAttackModel : FBaseAttackModel
{
    explicit FSkillAttackModel(int32 totalDamage = 0, int32 baseDamage = 0, int32 fixedDamage = 0) :
        FBaseAttackModel(totalDamage),
        BaseDamageValue(baseDamage),
        FixedDamageValue(fixedDamage)
    {
    }

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FSkillAttackModel)

    // ����ֵ����������˺�ֵ���������￹���ˡ����ڹ�����εļ��ܣ�ֵΪ���ι������
    int32 BaseDamageValue;
    // �̶��˺����ͱ�������ֱ�������˺�ֵ�й�
    int32 FixedDamageValue;
};
