#pragma once

#include <string>

#include <Platform.h>


/**
 * 仙术信息
 */
struct PAL4_API FMagicData
{
    // 仙术ID
    int32 ID;
    // 仙术名称
    std::string Name;
    // 仙术说明
    std::string Description;
    // 效果说明
    std::string EffectDescription;

    // AI指令类型
    uint8 AICommandType;
    // 仙术是否可在非战斗情况使用
    uint8 CanUseInSystem;
    // 攻击动作类型
    uint8 ActType;
    // 仙术目标
    uint8 TargetType;
    // 五灵属性
    uint8 WulingType;
    // 开启该仙术需要在该系有的最低仙灵点数
    uint8 PreviaMagicPoint;
    // 学习该仙术所需仙灵点数
    uint8 StudyMagicPoint;
    // 必须习得的前置技能ID
    int32 PreviaSkillID;

    // 附加技能ID
    int32 SkillID;
    // 消耗神值
    int32 ManaConsumeValue;

    // 施放者动作ID
    int32 ActorActionID;
    // 目标方特效ID
    int32 TargetEffectID;
    // 目标方特效挂载点
    uint8 TargetEffectPos;
};
