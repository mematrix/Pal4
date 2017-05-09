#pragma once

#include <string>

#include <Platform.h>


/**
 * 装备数据
 */
struct PAL4_API FEquipData
{
    // 装备ID
    int32 ID;
    // 装备名称
    std::string Name;
    // 装备信息描述
    std::string Description;

    // 装备类型
    uint8 Class;
    // 是否双手武器
    bool TwoHandedWeapon;
    // 天河穿戴等级下限。0表示不适合穿戴
    int32 LevelLimitOfTianhe;
    // 菱纱穿戴等级下限。0表示不适合穿戴
    int32 LevelLimitOfLingsha;
    // 梦璃穿戴等级下限。0表示不适合穿戴
    int32 LevelLimitOfMengli;
    // 紫英穿戴等级下限。0表示不适合穿戴
    int32 LevelLimitOfZiying;

    // 金钱价格
    int32 Price;
    // 挂载技能ID
    int32 SkillID;
    // 灵容量
    uint8 NimbusValue;
    // 潜力
    uint8 Capacity;

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

    // 二维图标
    int32 IconID2D;
    // 三维模型编号
    int32 ModelID3D;
    // 三维贴图编号
    int32 MapID3D;
};
