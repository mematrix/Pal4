#pragma once

#include <Platform.h>

#include "../EnumType/ERace.h"
#include "../EnumType/EPhysicalAttack.h"


struct PAL4_API FCharacterBasicInfo
{
    // 指示是否是玩家阵营的角色
    //bool IsPlayer;
    // 角色ID，用于获取全局信息，例如名称、头像等
    int32 ID;
    // 人物名称
    FName Name;

    // 等级
    int32 Level;
    // 经验值。对于主角是当前等级的经验，对于怪物则是被击败后可获取的经验
    int32 Experience;
    
    // 精上限值
    int32 MaxHealthPoint;
    // 神上限值
    int32 MaxManaPoint;
    // 气上限值
    int32 MaxCraftPoint;

    // 精
    int32 HealthPoint;
    // 神
    int32 ManaPoint;
    // 气
    int32 CraftPoint;

    // 五系仙术技能点
    uint8 MagicPoints[5];
    // 种族
    ERace Race;
    // 物理攻击类型
    EPhysicalAttackType PhysicalAttackType;
    // 物理攻击目标
    EPhysicalAttackTarget PhysicalAttackTarget;
};
