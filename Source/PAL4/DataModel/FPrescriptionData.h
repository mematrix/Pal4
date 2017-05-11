#pragma once

#include <string>

#include <Platform.h>


struct PAL4_API FPrescriptionData
{
    // �䷽ID
    int32 ID;
    // �䷽����
    std::string Name;
    // �䷽����
    std::string Description;
    // �䷽����˵��
    std::string EffectDescription;

    uint8 Type;
    //
    bool CanUseOnSword;
    //
    bool CanUseOnDoubleSword;
    //
    bool CanUseOnInstrument;
    //
    bool CanUseOnHeadArmor;
    //
    bool CanUseOnBodyArmor;
    //
    bool CanUseOnFootArmor;
    //
    bool CanUseOnOrnament;

    //
    int32 SynthesisPropID;
    //
    uint8 PotentialExpectedValue;
    //
    uint8 NimbusRequiredValue;
    //
    int32 SkillID;

    //
    int32 Price;
    //
    int32 Material1ID;
    //
    int32 Material1Count;
    //
    int32 Material2ID;
    //
    int32 Material2Count;
    //
    int32 Material3ID;
    //
    int32 Material3Count;
    //
    int32 Material4ID;
    //
    int32 Material4Count;

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
};
