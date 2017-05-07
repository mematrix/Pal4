#pragma once

#include <string>

#include <Platform.h>


/**
 * 怪物数据
 */
struct PAL4_API FMonsterData
{
    // 角色ID，用于获取全局信息，例如名称、头像等
    int32 ID;
    // 人物名称
    std::string Name;
    // 怪物信息描述
    std::string Description;

    // 种族
    int8 Race;
    // 是否Boss
    bool IsBoss;
    // AI操作类型
    int8 AIType;

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
    // 反击率附加。实际百分比*100
    int32 HitbackRate;

    // 被击败后可获取的经验
    int32 Experience;
    // 等级
    int32 Level;

    // 物理攻击目标
    int8 PhysicalAttackTarget;
    // 物理攻击类型
    int8 PhysicalAttackType;

    // 技能1ID
    int32 SkillID1;
    // 技能2ID
    int32 SkillID2;
    // 技能3ID
    int32 SkillID3;
    // 技能4ID
    int32 SkillID4;
    // 技能5ID
    int32 SkillID5;
    // 技能6ID
    int32 SkillID6;

    // 可偷窃物品ID。注：物品ID为金钱ID时代表可偷窃金钱。
    // 因为仙剑四数据库中数据显示没有怪物可以同时偷窃到金钱与物品，因此此处将其合并了
    int32 StealPropID;
    // 偷窃物品数量。对于金钱来说就是偷窃金钱数
    int32 StealPropCount;
    // 掉落物品1ID
    int32 DropPropID1;
    // 掉落物品1概率。以10000为基数计算百分比
    int32 DropPropProbability1;
    // 掉落物品2ID
    int32 DropPropID2;
    // 掉落物品2概率。以10000为基数计算百分比
    int32 DropPropProbability2;
    // 掉落物品3ID
    int32 DropPropID3;
    // 掉落物品3概率。以10000为基数计算百分比
    int32 DropPropProbability3;
    // 掉落物品4ID
    int32 DropPropID4;
    // 掉落物品4概率。以10000为基数计算百分比
    int32 DropPropProbability4;
    // 掉落金钱最小值
    int32 DropMoneyMinValue;
    // 掉落金钱最大值
    int32 DropMoneyMaxValue;

    // 我方气增加数值
    int32 CraftIncreaseValueOfRole;
    // 气初始化值
    int32 CraftInitPoint;
    // Debuff免疫信息
    int32 ImmuneFlags;

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
    // 死亡音效
    std::string DeathSound;
};
