#pragma once

#include <Platform.h>

#include "Util/BitUtil.h"


/**
 * 一些可以在战斗过程中被改变的属性值类型。根据当前仙剑四各种技能效果以及仙剑四游戏数据库整理。
 * 以flag方式定义，支持位操作。
 */
enum class PAL4_API ECharacterStatusType : int32
{
    // 武
    Attack = 1 << 0,
    // 运
    Luck = 1 << 1,
    // 灵
    Nimbus = 1 << 2,
    // 速
    Speed = 1 << 3,
    // 防
    Defence = 1 << 4,

    // 直接物理伤害追加
    PhysicalDamageAttach = 1 << 5,
    // 水系元素伤害追加
    WaterElementalDamageAttach = 1 << 6,
    // 火系元素伤害追加
    FireElementalDamageAttach = 1 << 7,
    // 雷系元素伤害追加
    ThunderElementalDamageAttach = 1 << 8,
    // 风系元素伤害追加
    WindElementalDamageAttach = 1 << 9,
    // 土系元素伤害追加
    SoilElementalDamageAttach = 1 << 10,

    // 物理抗性
    PhysicalResistance = 1 << 11,
    // 水系仙术抗性
    WaterMagicResistance = 1 << 12,
    // 火系仙术抗性
    FireMagicResistance = 1 << 13,
    // 雷系仙术抗性
    ThunderMagicResistance = 1 << 14,
    // 风系仙术抗性
    WindMagicResistance = 1 << 15,
    // 土系仙术抗性
    SoilMagicResistance = 1 << 16,

    // 物理伤害反弹
    PhysicalDamageBounce = 1 << 17,
    // 水属性伤害反弹
    WaterElementalDamageBounce = 1 << 18,
    // 火属性伤害反弹
    FireElementalDamageBounce = 1 << 19,
    // 雷属性伤害反弹
    ThunderElementalDamageBounce = 1 << 20,
    // 风属性伤害反弹
    WindElementalDamageBounce = 1 << 21,
    // 土属性伤害反弹
    SoilElementalDamageBounce = 1 << 22,

    // 格挡率
    BlockRate = 1 << 23,
    // 闪避率
    DodgeRate = 1 << 24,
    // 命中率
    HitRate = 1 << 25,
    // 暴击率
    CritRate = 1 << 26,

    PropertyMask = 1 << 27 - 1
};

constexpr uint32 PropertySetCount = static_cast<uint32>(GetLowBitIndex(static_cast<int32>(ECharacterStatusType::PropertyMask) + 1));
