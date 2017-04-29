#pragma once

#include <Platform.h>

#include "Util/BitUtil.h"


/**
 * һЩ������ս�������б��ı������ֵ���͡����ݵ�ǰ�ɽ��ĸ��ּ���Ч���Լ��ɽ�����Ϸ���ݿ�����
 * ��flag��ʽ���壬֧��λ������
 */
enum class PAL4_API ECharacterStatusType : int32
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

    // ֱ�������˺�׷��
    PhysicalDamageAttach,
    // ˮϵԪ���˺�׷��
    WaterElementalDamageAttach,
    // ��ϵԪ���˺�׷��
    FireElementalDamageAttach,
    // ��ϵԪ���˺�׷��
    ThunderElementalDamageAttach,
    // ��ϵԪ���˺�׷��
    WindElementalDamageAttach,
    // ��ϵԪ���˺�׷��
    SoilElementalDamageAttach,

    // ������
    PhysicalResistance,
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

    // �����˺�����
    PhysicalDamageBounce,
    // ˮ�����˺�����
    WaterElementalDamageBounce,
    // �������˺�����
    FireElementalDamageBounce,
    // �������˺�����
    ThunderElementalDamageBounce,
    // �������˺�����
    WindElementalDamageBounce,
    // �������˺�����
    SoilElementalDamageBounce,

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
