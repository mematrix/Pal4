#pragma once

#include "FBaseAttackModel.h"

class ICharacterBattleDelegate;


/**
 * 普通攻击额外状态：暴击闪避格挡
 */
enum class PAL4_API ENormalAttackExtroStatus
{
    None,
    // 暴击
    Crit,
    // 闪避
    Dodge,
    // 格挡
    Block,
    // 免疫
    Immune
};

/**
 * 普通攻击伤害
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

    // 普通武力原始伤害值（没有计算物抗减伤效果）
    int32 AttackDamageValue;
    // 直接物理伤害值
    int32 DirectDamageValue;
    // 元素伤害值
    int32 ElementalDamageValue;
    
    // 额外状态
    ENormalAttackExtroStatus ExtroStatus;
    // 援助者。nullptr表示无援助者，否则指向施展援助的对象（而不是被援助的对象）
    ICharacterBattleDelegate* Aid;
};

