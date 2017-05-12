#pragma once

#include <string>

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

    // 二维图标
    int32 IconID2D;
    // 三维模型编号
    int32 ModelID3D;
    // 三维贴图编号
    int32 MapID3D;
    // 受伤音效1
    std::string InjuredSound1;
    // 受伤音效2
    std::string InjuredSound2;
    // 受伤音效3
    std::string InjuredSound3;
};
