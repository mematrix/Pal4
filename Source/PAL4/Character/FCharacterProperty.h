// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PAL4.h"
#include "BattleSystem/FBattleSystem.h"

/**
 * 
 */
class PAL4_API FCharacterBasicInfo
{
    friend class FBattleSystem;

public:
	FCharacterBasicInfo();
	~FCharacterBasicInfo();

protected:
    // 攻击命中后气增量
    virtual int32 CraftIncreaseWhenAttackHit(int32 hitCount) = 0;
    // 被攻击命中后的气增量
    virtual int32 CraftIncreaseWhenBeAttacked() = 0;



private:
    // 经验值
    int32 Experience;

    // 精
    int32 HealthPoint;
    // 神
    int32 ManaPoint;
    // 气
    int32 CraftPoint;
    
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
