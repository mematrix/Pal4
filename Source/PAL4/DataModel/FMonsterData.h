#pragma once

#include <string>

#include <Platform.h>


/**
 * ��������
 */
struct PAL4_API FMonsterData
{
    // ��ɫID�����ڻ�ȡȫ����Ϣ���������ơ�ͷ���
    int32 ID;
    // ��������
    std::string Name;
    // ������Ϣ����
    std::string Description;

    // ����
    int8 Race;
    // �Ƿ�Boss
    bool IsBoss;
    // AI��������
    int8 AIType;

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
    // �����ʸ��ӡ�ʵ�ʰٷֱ�*100
    int32 HitbackRate;

    // �����ܺ�ɻ�ȡ�ľ���
    int32 Experience;
    // �ȼ�
    int32 Level;

    // ������Ŀ��
    int8 PhysicalAttackTarget;
    // ����������
    int8 PhysicalAttackType;

    // ����1ID
    int32 SkillID1;
    // ����2ID
    int32 SkillID2;
    // ����3ID
    int32 SkillID3;
    // ����4ID
    int32 SkillID4;
    // ����5ID
    int32 SkillID5;
    // ����6ID
    int32 SkillID6;

    // ��͵����ƷID��ע����ƷIDΪ��ǮIDʱ�����͵�Խ�Ǯ��
    // ��Ϊ�ɽ������ݿ���������ʾû�й������ͬʱ͵�Ե���Ǯ����Ʒ����˴˴�����ϲ���
    int32 StealPropID;
    // ͵����Ʒ���������ڽ�Ǯ��˵����͵�Խ�Ǯ��
    int32 StealPropCount;
    // ������Ʒ1ID
    int32 DropPropID1;
    // ������Ʒ1���ʡ���10000Ϊ��������ٷֱ�
    int32 DropPropProbability1;
    // ������Ʒ2ID
    int32 DropPropID2;
    // ������Ʒ2���ʡ���10000Ϊ��������ٷֱ�
    int32 DropPropProbability2;
    // ������Ʒ3ID
    int32 DropPropID3;
    // ������Ʒ3���ʡ���10000Ϊ��������ٷֱ�
    int32 DropPropProbability3;
    // ������Ʒ4ID
    int32 DropPropID4;
    // ������Ʒ4���ʡ���10000Ϊ��������ٷֱ�
    int32 DropPropProbability4;
    // �����Ǯ��Сֵ
    int32 DropMoneyMinValue;
    // �����Ǯ���ֵ
    int32 DropMoneyMaxValue;

    // �ҷ���������ֵ
    int32 CraftIncreaseValueOfRole;
    // ����ʼ��ֵ
    int32 CraftInitPoint;
    // Debuff������Ϣ
    int32 ImmuneFlags;

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
    // ������Ч
    std::string DeathSound;
};
