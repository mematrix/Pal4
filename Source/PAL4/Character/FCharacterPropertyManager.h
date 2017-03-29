// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class PAL4_API FCharacterPropertyManager
{
public:
	FCharacterPropertyManager();
	~FCharacterPropertyManager();

    // 角色是否是由玩家控制的一方，true表示玩家一方，false表示敌方（即AI怪物）
    bool IsPlayer() const;
    // 角色是否存活
    bool IsAlive() const;
};
