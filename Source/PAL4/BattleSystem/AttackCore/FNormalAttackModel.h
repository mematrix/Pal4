#pragma once

#include "FBaseAttackModel.h"

class ICharacterBattleDelegate;


/**
 * ��ͨ��������״̬���������ܸ�
 */
enum class PAL4_API ENormalAttackExtroStatus
{
    None,
    // ����
    Crit,
    // ����
    Dodge,
    // ��
    Block,
    // ����
    Immune
};

/**
 * ��ͨ�����˺�
 */
struct PAL4_API FNormalAttackModel : FBaseAttackModel
{
    explicit FNormalAttackModel(int32 totalDamage = 0, int32 attackDamage = 0, int32 directDamage = 0, int32 elementalDamage = 0,
        ENormalAttackExtroStatus status = ENormalAttackExtroStatus::None, ICharacterBattleDelegate* aid = nullptr) :
        FBaseAttackModel(totalDamage),
        AttackDamageValue(attackDamage),
        DirectDamageValue(directDamage),
        ElementalDamageValue(elementalDamage),
        ExtroStatus(status),
        Aid(aid)
    {
    }
    
    MAKE_DEFAULT_COPY_CTOR_AND_OP(FNormalAttackModel)

    // ��ͨ����ԭʼ�˺�ֵ��û�м����￹����Ч����
    int32 AttackDamageValue;
    // ֱ�������˺�ֵ
    int32 DirectDamageValue;
    // Ԫ���˺�ֵ
    int32 ElementalDamageValue;
    
    // ����״̬
    ENormalAttackExtroStatus ExtroStatus;
    // Ԯ���ߡ�nullptr��ʾ��Ԯ���ߣ�����ָ��ʩչԮ���Ķ��󣨶����Ǳ�Ԯ���Ķ���
    ICharacterBattleDelegate* Aid;
};

