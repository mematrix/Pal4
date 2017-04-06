#pragma once

#include <Platform.h>

struct PAL4_API FCharacterStatusInfo
{
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
