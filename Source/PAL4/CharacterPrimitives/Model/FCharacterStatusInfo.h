#pragma once

#include <Platform.h>

struct PAL4_API FCharacterStatusInfo
{
    // 武
    int32 AttackPoint;
    // 运
    int32 LuckPoint;
    // 灵
    int32 NimbusPoint;
    // 速
    int32 SpeedPoint;
    // 防
    int32 DefencePoint;

    // 物理抗性。实际百分比*100
    int32 AttackResistance;
    // 水系仙术抗性。实际百分比*100
    int32 WaterMagicResistance;
    // 火系仙术抗性。实际百分比*100
    int32 FireMagicResistance;
    // 雷系仙术抗性。实际百分比*100
    int32 ThunderMagicResistance;
    // 风系仙术抗性。实际百分比*100
    int32 WindMagicResistance;
    // 土系仙术抗性。实际百分比*100
    int32 SoilMagicResistance;

    // 直接物理伤害
    int32 DirectAttackDamage;
    // 水系元素伤害
    int32 WaterElementalDamage;
    // 火系元素伤害
    int32 FireElementalDamage;
    // 雷系元素伤害
    int32 ThunderElementalDamage;
    // 风系元素伤害
    int32 WindElementalDamage;
    // 土系元素伤害
    int32 SoilElementalDamage;

    // 元素伤害抗性
    int32 ElementalResistance;

    // 格挡率。实际百分比*100
    int32 BlockRate;
    // 闪避率。实际百分比*100
    int32 DodgeRate;
    // 命中率。实际百分比*100
    int32 HitRate;
    // 暴击率。实际百分比*100
    int32 CritRate;
};
