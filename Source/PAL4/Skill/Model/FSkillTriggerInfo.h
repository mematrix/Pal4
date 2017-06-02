#pragma once

#include "Skill/Enum/ESkillAttribute.h"

class ICharacterDelegate;


/**
 * 技能触发情况及攻防人物信息
 */
struct PAL4_API FSkillTriggerInfo
{
    // 技能释放来源
    ESkillSource Source;
    // 攻击者
    ICharacterDelegate *Actor;
    // 攻击目标
    ICharacterDelegate *Target;
};
