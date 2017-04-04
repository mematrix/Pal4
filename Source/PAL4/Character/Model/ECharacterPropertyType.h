#pragma once

enum class PAL4_API ECharacterPropertyType
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

    // 物理抗性
    AttackResistance,
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

    // 直接物理伤害
    DirectAttackDamage,
    // 水系元素伤害
    WaterElementalDamage,
    // 火系元素伤害
    FireElementalDamage,
    // 雷系元素伤害
    ThunderElementalDamage,
    // 风系元素伤害
    WindElementalDamage,
    // 土系元素伤害
    SoilElementalDamage,

    // 元素伤害抗性
    ElementalResistance,

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

constexpr uint32 PropertySetCount = static_cast<uint32>(ECharacterPropertyType::PropertyEnd);

