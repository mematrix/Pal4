// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PAL4.h"
#include "BattleSystem/FBattleSystem.h"

/**
 * 
 */
class PAL4_API FCharacterProperty
{
public:
	FCharacterProperty();
	~FCharacterProperty();

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
    
    
};
