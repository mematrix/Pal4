#pragma once

enum class PAL4_API ECharacterPropertyType
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
