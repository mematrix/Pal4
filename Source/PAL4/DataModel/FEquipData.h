#pragma once

#include <string>

#include <Platform.h>


/**
 * װ������
 */
struct PAL4_API FEquipData
{
    // װ��ID
    int32 ID;
    // װ������
    std::string Name;
    // װ����Ϣ����
    std::string Description;

    // װ������
    uint8 Class;
    // �Ƿ�˫������
    bool TwoHandedWeapon;
    // ��Ӵ����ȼ����ޡ�0��ʾ���ʺϴ���
    int32 LevelLimitOfTianhe;
    // ��ɴ�����ȼ����ޡ�0��ʾ���ʺϴ���
    int32 LevelLimitOfLingsha;
    // ���������ȼ����ޡ�0��ʾ���ʺϴ���
    int32 LevelLimitOfMengli;
    // ��Ӣ�����ȼ����ޡ�0��ʾ���ʺϴ���
    int32 LevelLimitOfZiying;

    // ��Ǯ�۸�
    int32 Price;
    // ���ؼ���ID
    int32 SkillID;
    // ������
    uint8 NimbusValue;
    // Ǳ��
    uint8 Capacity;

    // �����ֵ
    int32 MaxHealthChange;
    // ��������
    int32 CraftIncreaseChange;
    // �����ֵ
    int32 MaxManaChange;

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
};
