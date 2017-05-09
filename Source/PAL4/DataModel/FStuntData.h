#pragma once

#include <string>

#include <Platform.h>


/**
 * 技能信息
 */
struct PAL4_API FStuntData
{
    // 特技ID
    int32 ID;
    // 特技名称
    std::string Name;
    // 特技说明
    std::string Description;
    // 效果说明
    std::string EffectDescription;

    // AI指令类型
    uint8 AICommandType;
    // 攻击动作类型
    uint8 ActType;
    // 等级下限
    uint8 LimitLevel;
    // 特技使用的武器
    uint8 Weapon;

    // 附加技能ID
    int32 SkillID;
    // 消耗气值
    int32 CraftConsumeValue;

    // 消耗物品1ID
    int32 ConsumeProp1ID;
    // 消耗物品1数量
    int32 ConsumeProp1Count;
    // 消耗物品2ID
    int32 ConsumeProp2ID;
    // 消耗物品2数量
    int32 ConsumeProp2Count;
    // 消耗物品3ID
    int32 ConsumeProp3ID;
    // 消耗物品3数量
    int32 ConsumeProp3Count;
    // 消耗物品4ID
    int32 ConsumeProp4ID;
    // 消耗物品4数量
    int32 ConsumeProp4Count;
    // 消耗物品5ID
    int32 ConsumeProp5ID;
    // 消耗物品5数量
    int32 ConsumeProp5Count;
    // 消耗金钱数量
    int32 ConsumeMoneyCount;

    // 必须拥有的物品ID
    int32 RequiredPropID;
    // 必须携带的技能ID
    int32 RequiredSkillID;

    // 施放者动作ID
    int32 ActorActionID;
    // 目标方特效ID
    int32 TargetEffectID;
    // 目标方特效挂载点
    uint8 TargetEffectPos;
};
