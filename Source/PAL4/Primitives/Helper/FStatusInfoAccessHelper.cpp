// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <crtdbg.h>

#include "FStatusInfoAccessHelper.h"
#include "../Model/FCharacterStatusInfo.h"


int32 FCharacterStatusInfo::* const PropertySet[PropertySetCount] =
{
    // ��
    &FCharacterStatusInfo::AttackPoint,
    // ��
    &FCharacterStatusInfo::LuckPoint,
    // ��
    &FCharacterStatusInfo::NimbusPoint,
    // ��
    &FCharacterStatusInfo::SpeedPoint,
    // ��
    &FCharacterStatusInfo::DefencePoint,

    // ֱ�������˺�����
    &FCharacterStatusInfo::PhysicalDamageAttach,
    // ˮϵԪ���˺�����
    &FCharacterStatusInfo::WaterElementalDamageAttach,
    // ��ϵԪ���˺�����
    &FCharacterStatusInfo::FireElementalDamageAttach,
    // ��ϵԪ���˺�����
    &FCharacterStatusInfo::ThunderElementalDamageAttach,
    // ��ϵԪ���˺�����
    &FCharacterStatusInfo::WindElementalDamageAttach,
    // ��ϵԪ���˺�����
    &FCharacterStatusInfo::SoilElementalDamageAttach,

    // ������
    &FCharacterStatusInfo::PhysicalResistance,
    // ˮϵ��������
    &FCharacterStatusInfo::WaterMagicResistance,
    // ��ϵ��������
    &FCharacterStatusInfo::FireMagicResistance,
    // ��ϵ��������
    &FCharacterStatusInfo::ThunderMagicResistance,
    // ��ϵ��������
    &FCharacterStatusInfo::WindMagicResistance,
    // ��ϵ��������
    &FCharacterStatusInfo::SoilMagicResistance,

    // �����˺�����
    &FCharacterStatusInfo::PhysicalDamageBounce,
    // ˮ�����˺�����
    &FCharacterStatusInfo::WaterElementalDamageBounce,
    // �������˺�����
    &FCharacterStatusInfo::FireElementalDamageBounce,
    // �������˺�����
    &FCharacterStatusInfo::ThunderElementalDamageBounce,
    // �������˺�����
    &FCharacterStatusInfo::WindElementalDamageBounce,
    // �������˺�����
    &FCharacterStatusInfo::SoilElementalDamageBounce,

    // ����
    &FCharacterStatusInfo::BlockRate,
    // ������
    &FCharacterStatusInfo::HitRate,
    // ������
    &FCharacterStatusInfo::CritRate //,
    // ������
    //&FCharacterStatusInfo::DodgeRate,
};

int32 FStatusInfoAccessHelper::GetPropertyValue(ECharacterStatusType type) const
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    return InfoModel.*GetPropertyPtr(type);
}

void FStatusInfoAccessHelper::SetPropertyValue(ECharacterStatusType type, int32 value) const
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    InfoModel.*GetPropertyPtr(type) = value;
}

void FStatusInfoAccessHelper::AddPropertyValue(ECharacterStatusType type, int32 value) const
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    InfoModel.*GetPropertyPtr(type) += value;
}

int32 FStatusInfoReader::GetPropertyValue(ECharacterStatusType type) const
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    return InfoModel.*GetPropertyPtr(type);
}
