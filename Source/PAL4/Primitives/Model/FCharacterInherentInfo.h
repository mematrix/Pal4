#pragma once

#include <NameTypes.h>
#include "Primitives/EnumType/ERace.h"
#include "Primitives/EnumType/EPhysicalAttack.h"


struct PAL4_API FCharacterInherentInfo
{
    // 角色ID，用于获取全局信息，例如名称、头像等
    int32 ID;
    // 人物名称
    FName Name;

    // 种族
    ERace Race;
    // 物理攻击类型
    EPhysicalAttackType PhysicalAttackType;
    // 物理攻击目标
    EPhysicalAttackTarget PhysicalAttackTarget;
};
