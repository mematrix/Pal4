#pragma once

#include <Platform.h>


struct PAL4_API FUpgradeData
{
    // �ȼ�
    int32 Level;
    // ����ֵ�������ֵ��������һ����
    int32 Experience;
    // �����ֵ
    int32 MaxHealthPoint;
    // �����ֵ
    int32 MaxManaPoint;
    // ��������
    int32 CraftIncreaseValue;

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
    // ˮ
    int32 WaterMagicPoint;
    // ��
    int32 FireMagicPoint;
    // ��
    int32 ThunderMagicPoint;
    // ��
    int32 WindMagicPoint;
    // ��
    int32 SoilMagicPoint;
    
    // ֱ�������˺�׷��
    int32 PhysicalDamageAttach;
    // ˮϵԪ���˺�׷��
    int32 WaterElementalDamageAttach;
    // ��ϵԪ���˺�׷��
    int32 FireElementalDamageAttach;
    // ��ϵԪ���˺�׷��
    int32 ThunderElementalDamageAttach;
    // ��ϵԪ���˺�׷��
    int32 WindElementalDamageAttach;
    // ��ϵԪ���˺�׷��
    int32 SoilElementalDamageAttach;

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

    // �����˺�������ʵ�ʰٷֱ�*100
    int32 PhysicalDamageBounce;
    // ˮ�����˺�������ʵ�ʰٷֱ�*100
    int32 WaterElementalDamageBounce;
    // �������˺�������ʵ�ʰٷֱ�*100
    int32 FireElementalDamageBounce;
    // �������˺�������ʵ�ʰٷֱ�*100
    int32 ThunderElementalDamageBounce;
    // �������˺�������ʵ�ʰٷֱ�*100
    int32 WindElementalDamageBounce;
    // �������˺�������ʵ�ʰٷֱ�*100
    int32 SoilElementalDamageBounce;

    // ���ʡ�ʵ�ʰٷֱ�*100
    int32 BlockRate;
    // �����ʡ�ʵ�ʰٷֱ�*100
    int32 HitRate;
    // �����ʡ�ʵ�ʰٷֱ�*100
    int32 CritRate;
};
