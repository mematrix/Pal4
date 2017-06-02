#pragma once

#include "Skill/FSkillResult.h"


struct PAL4_API FBasicInfoResultRecord
{
    // 基本信息结果。非空保证
    FBasicInfoResult *Result;
    // 攻击者。可能为nullptr
    ICharacterDelegate *Actor;
    // 攻击目标。保证非nullptr
    ICharacterDelegate *Target;
};


struct PAL4_API FStatusInfoResultRecord
{
    // 状态信息结果。非空保证
    FStatusInfoResult *Result;
    // 攻击者。可能为nullptr
    ICharacterDelegate *Actor;
    // 攻击目标。保证非nullptr
    ICharacterDelegate *Target;
};


struct PAL4_API FTriggerResultRecord
{
    // 触发信息结果。非空保证
    FTriggerResult *Result;
    // 攻击者。可能为nullptr
    ICharacterDelegate *Actor;
    // 攻击目标。保证非nullptr
    ICharacterDelegate *Target;
};


struct PAL4_API FCombatStatusResultRecord
{
    // 战斗状态信息结果。非空保证
    FCombatStatusResult *Result;
    // 攻击者。可能为nullptr
    ICharacterDelegate *Actor;
    // 攻击目标。保证非nullptr
    ICharacterDelegate *Target;
};
