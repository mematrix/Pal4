#pragma once

#include <Platform.h>

struct PAL4_API FCharacterBasicInfo
{
    // 指示是否是玩家阵营的角色
    bool IsPlayer;

    // 等级
    int32 Level;
    // 经验值
    int32 Experience;
    // 角色ID，用于获取全局信息，例如名称、头像等
    int32 ID;
    
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
    unsigned char MagicPoints[5];
};
