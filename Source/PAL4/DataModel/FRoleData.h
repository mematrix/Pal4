#pragma once

#include <string>

#include <Platform.h>


/**
 * 角色数据
 */
struct PAL4_API FRoleData
{
    // 角色ID，用于获取全局信息，例如名称、头像等
    int32 ID;
    // 人物名称
    std::string Name;

    // 种族
    int8 Race;
    // 物理攻击目标
    int8 PhysicalAttackTarget;
    // 物理攻击类型
    int8 PhysicalAttackType;

    // 对天河好感度
    int32 FavorOfTianhe;
    // 对菱纱好感度
    int32 FavorOfLingsha;
    // 对梦璃好感度
    int32 FavorOfMengli;
    // 对紫英好感度
    int32 FavorOfZiying;

    // 精上限值
    int32 MaxHealthPoint;
    // 气增加量
    int32 CraftIncreaseValue;
    // 神上限值
    int32 MaxManaPoint;

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
    // 受伤音效1
    std::string InjuredSound1;
    // 受伤音效2
    std::string InjuredSound2;
    // 受伤音效3
    std::string InjuredSound3;
};
