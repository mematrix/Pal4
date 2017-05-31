#pragma once

#include <Platform.h>

#include "Skill/Enum/ESkillType.h"
#include "Skill/Enum/ESkillTriggerType.h"
#include "Skill/Enum/ESkillAttribute.h"


struct PAL4_API FSkillInfo
{
    int32 ID;
    // 技能类别。战斗技能、地图技能等
    ESkillType Type;
    // 技能触发条件
    ESkillTriggerType TriggerType;
    // 攻击来源。特技仙术、或者被动触发等
    ESkillSource Source;
    // 技能所属分类。攻击辅助恢复等
    ESkillCategory Category;
};
