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
    Attack = 1 << 0,
    // ��
    Luck = 1 << 1,
    // ��
    Nimbus = 1 << 2,
    // ��
    Speed = 1 << 3,
    // ��
    Defence = 1 << 4,

    // ֱ�������˺�׷��
    PhysicalDamageAttach = 1 << 5,
    // ˮϵԪ���˺�׷��
    WaterElementalDamageAttach = 1 << 6,
    // ��ϵԪ���˺�׷��
    FireElementalDamageAttach = 1 << 7,
    // ��ϵԪ���˺�׷��
    ThunderElementalDamageAttach = 1 << 8,
    // ��ϵԪ���˺�׷��
    WindElementalDamageAttach = 1 << 9,
    // ��ϵԪ���˺�׷��
    SoilElementalDamageAttach = 1 << 10,

    // ������
    PhysicalResistance = 1 << 11,
    // ˮϵ��������
    WaterMagicResistance = 1 << 12,
    // ��ϵ��������
    FireMagicResistance = 1 << 13,
    // ��ϵ��������
    ThunderMagicResistance = 1 << 14,
    // ��ϵ��������
    WindMagicResistance = 1 << 15,
    // ��ϵ��������
    SoilMagicResistance = 1 << 16,

    // �����˺�����
    PhysicalDamageBounce = 1 << 17,
    // ˮ�����˺�����
    WaterElementalDamageBounce = 1 << 18,
    // �������˺�����
    FireElementalDamageBounce = 1 << 19,
    // �������˺�����
    ThunderElementalDamageBounce = 1 << 20,
    // �������˺�����
    WindElementalDamageBounce = 1 << 21,
    // �������˺�����
    SoilElementalDamageBounce = 1 << 22,

    // ����
    BlockRate = 1 << 23,
    // ������
    DodgeRate = 1 << 24,
    // ������
    HitRate = 1 << 25,
    // ������
    CritRate = 1 << 26,

    PropertyMask = 1 << 27 - 1
};

constexpr uint32 PropertySetCount = static_cast<uint32>(GetLowBitIndex(static_cast<int32>(ECharacterStatusType::PropertyMask) + 1));
