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
    // �������к�������
    virtual int32 CraftIncreaseWhenAttackHit(int32 hitCount) = 0;
    // ���������к��������
    virtual int32 CraftIncreaseWhenBeAttacked() = 0;



private:
    // ����ֵ
    int32 Experience;

    // ��
    int32 HealthPoint;
    // ��
    int32 ManaPoint;
    // ��
    int32 CraftPoint;
    
    
};
