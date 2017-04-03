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
    
    // ��
    int32 AttackPoint;
    // ��
    int32 LuckPoint;
    // ��
    int32 NimbusPoint;
    // ��
    int32 SpeedPoint;
    // ��
    int32 DefencePoint;

    // �����ԡ�ʵ�ʰٷֱ�*100
    int32 AttackResistance;
    // ˮϵ�������ԡ�ʵ�ʰٷֱ�*100
    int32 WaterMagicResistance;
    // ��ϵ�������ԡ�ʵ�ʰٷֱ�*100
    int32 FireMagicResistance;
    // ��ϵ�������ԡ�ʵ�ʰٷֱ�*100
    int32 ThunderMagicResistance;
    // ��ϵ�������ԡ�ʵ�ʰٷֱ�*100
    int32 WindMagicResistance;
    // ��ϵ�������ԡ�ʵ�ʰٷֱ�*100
    int32 SoilMagicResistance;

    // ֱ�������˺�
    int32 DirectAttackDamage;
    // ˮϵԪ���˺�
    int32 WaterElementalDamage;
    // ��ϵԪ���˺�
    int32 FireElementalDamage;
    // ��ϵԪ���˺�
    int32 ThunderElementalDamage;
    // ��ϵԪ���˺�
    int32 WindElementalDamage;
    // ��ϵԪ���˺�
    int32 SoilElementalDamage;

    // Ԫ���˺�����
    int32 ElementalResistance;

    // ���ʡ�ʵ�ʰٷֱ�*100
    int32 BlockRate;
    // �����ʡ�ʵ�ʰٷֱ�*100
    int32 DodgeRate;
    // �����ʡ�ʵ�ʰٷֱ�*100
    int32 HitRate;
    // �����ʡ�ʵ�ʰٷֱ�*100
    int32 CritRate;
};
