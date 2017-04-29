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
    Attack = 0,
    // 运
    Luck,
    // 灵
    Nimbus,
    // 速
    Speed,
    // 防
    Defence,

    // 直接物理伤害追加
    PhysicalDamageAttach,
    // 水系元素伤害追加
    WaterElementalDamageAttach,
    // 火系元素伤害追加
    FireElementalDamageAttach,
    // 雷系元素伤害追加
    ThunderElementalDamageAttach,
    // 风系元素伤害追加
    WindElementalDamageAttach,
    // 土系元素伤害追加
    SoilElementalDamageAttach,

    // 物理抗性
    PhysicalResistance,
    // 水系仙术抗性
    WaterMagicResistance,
    // 火系仙术抗性
    FireMagicResistance,
    // 雷系仙术抗性
    ThunderMagicResistance,
    // 风系仙术抗性
    WindMagicResistance,
    // 土系仙术抗性
    SoilMagicResistance,

    // 物理伤害反弹
    PhysicalDamageBounce,
    // 水属性伤害反弹
    WaterElementalDamageBounce,
    // 火属性伤害反弹
    FireElementalDamageBounce,
    // 雷属性伤害反弹
    ThunderElementalDamageBounce,
    // 风属性伤害反弹
    WindElementalDamageBounce,
    // 土属性伤害反弹
    SoilElementalDamageBounce,

    // 格挡率
    BlockRate,
    // 闪避率
    DodgeRate,
    // 命中率
    HitRate,
    // 暴击率
    CritRate,

    PropertyEnd
};

constexpr uint32 PropertySetCount = static_cast<uint32>(ECharacterStatusType::PropertyEnd);
