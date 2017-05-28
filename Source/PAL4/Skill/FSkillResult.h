#pragma once

#include <vector>
#include <functional>

#include <Platform.h>
#include <SharedPointer.h>

#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/EnumType/ESkillTriggerType.h"
#include "Primitives/EnumType/ECombatStatus.h"
#include "Primitives/EnumType/EAttackSpecialStatus.h"

class ICharacterDelegate;


/**
 * 描述基本信息（精气神）变化结果。正值为增加，负值为减少
 */
struct PAL4_API FBasicInfoResult
{
    // 精变化量
    int32 HealthValue;
    // 神变化量
    int32 ManaValue;
    // 气变化量
    int32 CraftValue;
    // 异常状态：暴击闪避格挡
    EAttackSpecialStatus SpecialStatus;
};


/**
 * 描述状态信息变换结果
 */
struct PAL4_API FStatusInfoResult
{
    // 作用状态类型
    ECharacterStatusType StatusType;
    // 状态变换函数
    std::function<int32(int32)> TransformAction;
    // 有效回合数。0表示永久有效
    uint32 ValidRoundNum;
};


/**
 * 触发类型结果信息
 */
struct PAL4_API FTriggerResult
{
    // 技能触发类型
    ESkillTriggerType TriggerType;
    // 触发回调函数
    std::function<void(ICharacterDelegate&, ICharacterDelegate&)> TriggerFunc;
};


/**
 * 战斗状态结果信息
 */
struct PAL4_API FCombatStatusResult
{
    // 战斗状态类型，Buff、Debuff
    ECombatStatus StatusType;
    // 战斗状态值，根据类型取对应值
    union
    {
        EBuff Buff;
        EPoison Poison;
        EDebuff Debuff;
        bool CanResurrect;
        bool Invisible;
    } Status;
    // 状态效果持续最大回合数
    uint32 MaxEffectRoundNum;
};


/**
 * 技能释放结果描述
 */
struct PAL4_API FSkillResult
{
    // 基本信息结果。通常为0或1个数据，只有分次伤害时才会有多个数据
    TSharedPtr<std::vector<FBasicInfoResult>> BasicInfoResult;
    // 状态信息结果。每一种状态一个数据
    TSharedPtr<std::vector<FStatusInfoResult>> StatusInfoResult;
    // 触发信息结果。每一种情况一个数据
    TSharedPtr<std::vector<FTriggerResult>> TriggerResult;
    // 战斗Buff和Debuff结果。无改变则为nullptr
    TSharedPtr<FCombatStatusResult> CombatStatusResult;
};
