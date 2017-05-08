#pragma once

#include <string>

#include <Platform.h>


/**
 * ��ɫ����
 */
struct PAL4_API FRoleData
{
    // ��ɫID�����ڻ�ȡȫ����Ϣ���������ơ�ͷ���
    int32 ID;
    // ��������
    std::string Name;

    // ����
    int8 Race;
    // ������Ŀ��
    int8 PhysicalAttackTarget;
    // ����������
    int8 PhysicalAttackType;

    // ����Ӻøж�
    int32 FavorOfTianhe;
    // ����ɴ�øж�
    int32 FavorOfLingsha;
    // �������øж�
    int32 FavorOfMengli;
    // ����Ӣ�øж�
    int32 FavorOfZiying;

    // ������ֵ
    int32 MaxHealthPoint;
    // ��������
    int32 CraftIncreaseValue;
    // ������ֵ
    int32 MaxManaPoint;

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
    uint8 WaterMagicPoint;
    // ��
    uint8 FireMagicPoint;
    // ��
    uint8 ThunderMagicPoint;
    // ��
    uint8 WindMagicPoint;
    // ��
    uint8 SoilMagicPoint;

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
    int32 PhysicalResistance;
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

    // �����ʸ��ӡ�ʵ�ʰٷֱ�*100
    int32 CritRate;
    // ���ʸ��ӡ�ʵ�ʰٷֱ�*100
    int32 BlockRate;
    // �����ʸ��ӡ�ʵ�ʰٷֱ�*100
    int32 HitRate;

    // ��άͼ��
    int32 IconID2D;
    // ��άģ�ͱ��
    int32 ModelID3D;
    // ��ά��ͼ���
    int32 MapID3D;
    // ������Ч1
    std::string InjuredSound1;
    // ������Ч2
    std::string InjuredSound2;
    // ������Ч3
    std::string InjuredSound3;
};
