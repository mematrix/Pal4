#pragma once

#include <Platform.h>


enum class PAL4_API ECharacterStatusType
{
    // ��
    Attack = 0,
    // ��
    Luck,
    // ��
    Nimbus,
    // ��
    Speed,
    // ��
    Defence,

    // ������
    AttackResistance,
    // ˮϵ��������
    WaterMagicResistance,
    // ��ϵ��������
    FireMagicResistance,
    // ��ϵ��������
    ThunderMagicResistance,
    // ��ϵ��������
    WindMagicResistance,
    // ��ϵ��������
    SoilMagicResistance,

    // ֱ�������˺�
    DirectAttackDamage,
    // ˮϵԪ���˺�
    WaterElementalDamage,
    // ��ϵԪ���˺�
    FireElementalDamage,
    // ��ϵԪ���˺�
    ThunderElementalDamage,
    // ��ϵԪ���˺�
    WindElementalDamage,
    // ��ϵԪ���˺�
    SoilElementalDamage,

    // Ԫ���˺�����
    ElementalResistance,

    // ����
    BlockRate,
    // ������
    DodgeRate,
    // ������
    HitRate,
    // ������
    CritRate,

    PropertyEnd
};

constexpr uint32 PropertySetCount = static_cast<uint32>(ECharacterStatusType::PropertyEnd);

