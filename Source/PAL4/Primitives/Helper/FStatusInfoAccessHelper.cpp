// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <crtdbg.h>

#include "FStatusInfoAccessHelper.h"
#include "../Model/FCharacterStatusInfo.h"

int32 FCharacterStatusInfo::* const FStatusInfoAccessHelper::PropertySet[PropertySetCount] =
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

    // ������
    &FCharacterStatusInfo::AttackResistance,
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

    // ֱ�������˺�
    &FCharacterStatusInfo::DirectAttackDamage,
    // ˮϵԪ���˺�
    &FCharacterStatusInfo::WaterElementalDamage,
    // ��ϵԪ���˺�
    &FCharacterStatusInfo::FireElementalDamage,
    // ��ϵԪ���˺�
    &FCharacterStatusInfo::ThunderElementalDamage,
    // ��ϵԪ���˺�
    &FCharacterStatusInfo::WindElementalDamage,
    // ��ϵԪ���˺�
    &FCharacterStatusInfo::SoilElementalDamage,

    // Ԫ���˺�����
    &FCharacterStatusInfo::ElementalResistance,

    // ����
    &FCharacterStatusInfo::BlockRate,
    // ������
    &FCharacterStatusInfo::DodgeRate,
    // ������
    &FCharacterStatusInfo::HitRate,
    // ������
    &FCharacterStatusInfo::CritRate,
};

int32 FStatusInfoAccessHelper::GetPropertyValue(ECharacterStatusType type) const
{
    _ASSERT(static_cast<uint32>(type) < static_cast<uint32>(ECharacterStatusType::PropertyMask));
    return InfoModel.*GetPropertyPtr(type);
}

void FStatusInfoAccessHelper::SetPropertyValue(ECharacterStatusType type, int32 value) const
{
    _ASSERT(static_cast<uint32>(type) < static_cast<uint32>(ECharacterStatusType::PropertyMask));
    InfoModel.*GetPropertyPtr(type) = value;
}

void FStatusInfoAccessHelper::AddPropertyValue(ECharacterStatusType type, int32 value) const
{
    _ASSERT(static_cast<uint32>(type) < static_cast<uint32>(ECharacterStatusType::PropertyMask));

}
