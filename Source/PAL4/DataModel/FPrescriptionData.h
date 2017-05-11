#pragma once

#include <string>

#include <Platform.h>


struct PAL4_API FPrescriptionData
{
    // 配方ID
    int32 ID;
    // 配方名称
    std::string Name;
    // 配方描述
    std::string Description;
    // 配方属性说明
    std::string EffectDescription;

    uint8 Type;
    //
    bool CanUseOnSword;
    //
    bool CanUseOnDoubleSword;
    //
    bool CanUseOnInstrument;
    //
    bool CanUseOnHeadArmor;
    //
    bool CanUseOnBodyArmor;
    //
    bool CanUseOnFootArmor;
    //
    bool CanUseOnOrnament;

    //
    int32 SynthesisPropID;
    //
    uint8 PotentialExpectedValue;
    //
    uint8 NimbusRequiredValue;
    //
    int32 SkillID;

    //
    int32 Price;
    //
    int32 Material1ID;
    //
    int32 Material1Count;
    //
    int32 Material2ID;
    //
    int32 Material2Count;
    //
    int32 Material3ID;
    //
    int32 Material3Count;
    //
    int32 Material4ID;
    //
    int32 Material4Count;

    // 精最大值
    int32 MaxHealthChange;
    // 气增加量
    int32 CraftIncreaseChange;
    // 神最大值
    int32 MaxManaChange;

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
    uint8 WaterMagicPoint;
    // 火
    uint8 FireMagicPoint;
    // 雷
    uint8 ThunderMagicPoint;
    // 风
    uint8 WindMagicPoint;
    // 土
    uint8 SoilMagicPoint;

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
    int32 PhysicalResistance;
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

    // 暴击率附加。实际百分比*100
    int32 CritRate;
    // 格挡率附加。实际百分比*100
    int32 BlockRate;
    // 命中率附加。实际百分比*100
    int32 HitRate;
};
