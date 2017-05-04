#pragma once

#include <Platform.h>


struct PAL4_API FUpgradeData
{
    // 等级
    int32 Level;
    // 经验值（到达此值可升级下一级）
    int32 Experience;
    // 精最大值
    int32 MaxHealthPoint;
    // 神最大值
    int32 MaxManaPoint;
    // 气增加量
    int32 CraftIncreaseValue;

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
    // 水
    int32 WaterMagicPoint;
    // 火
    int32 FireMagicPoint;
    // 雷
    int32 ThunderMagicPoint;
    // 风
    int32 WindMagicPoint;
    // 土
    int32 SoilMagicPoint;
    
    // 直接物理伤害追加
    int32 PhysicalDamageAttach;
    // 水系元素伤害追加
    int32 WaterElementalDamageAttach;
    // 火系元素伤害追加
    int32 FireElementalDamageAttach;
    // 雷系元素伤害追加
    int32 ThunderElementalDamageAttach;
    // 风系元素伤害追加
    int32 WindElementalDamageAttach;
    // 土系元素伤害追加
    int32 SoilElementalDamageAttach;

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

    // 物理伤害反弹。实际百分比*100
    int32 PhysicalDamageBounce;
    // 水属性伤害反弹。实际百分比*100
    int32 WaterElementalDamageBounce;
    // 火属性伤害反弹。实际百分比*100
    int32 FireElementalDamageBounce;
    // 雷属性伤害反弹。实际百分比*100
    int32 ThunderElementalDamageBounce;
    // 风属性伤害反弹。实际百分比*100
    int32 WindElementalDamageBounce;
    // 土属性伤害反弹。实际百分比*100
    int32 SoilElementalDamageBounce;

    // 格挡率。实际百分比*100
    int32 BlockRate;
    // 命中率。实际百分比*100
    int32 HitRate;
    // 暴击率。实际百分比*100
    int32 CritRate;
};
