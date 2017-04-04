// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <crtdbg.h>

#include "FInfoModelAccessHelper.h"
#include "../Model/FCharacterInfoModel.h"

int32 FCharacterInfoModel::* const FInfoModelAccessHelper::PropertySet[PropertySetCount] =
{
    // ��
    &FCharacterInfoModel::AttackPoint,
    // ��
    &FCharacterInfoModel::LuckPoint,
    // ��
    &FCharacterInfoModel::NimbusPoint,
    // ��
    &FCharacterInfoModel::SpeedPoint,
    // ��
    &FCharacterInfoModel::DefencePoint,

    // ������
    &FCharacterInfoModel::AttackResistance,
    // ˮϵ��������
    &FCharacterInfoModel::WaterMagicResistance,
    // ��ϵ��������
    &FCharacterInfoModel::FireMagicResistance,
    // ��ϵ��������
    &FCharacterInfoModel::ThunderMagicResistance,
    // ��ϵ��������
    &FCharacterInfoModel::WindMagicResistance,
    // ��ϵ��������
    &FCharacterInfoModel::SoilMagicResistance,

    // ֱ�������˺�
    &FCharacterInfoModel::DirectAttackDamage,
    // ˮϵԪ���˺�
    &FCharacterInfoModel::WaterElementalDamage,
    // ��ϵԪ���˺�
    &FCharacterInfoModel::FireElementalDamage,
    // ��ϵԪ���˺�
    &FCharacterInfoModel::ThunderElementalDamage,
    // ��ϵԪ���˺�
    &FCharacterInfoModel::WindElementalDamage,
    // ��ϵԪ���˺�
    &FCharacterInfoModel::SoilElementalDamage,

    // Ԫ���˺�����
    &FCharacterInfoModel::ElementalResistance,

    // ����
    &FCharacterInfoModel::BlockRate,
    // ������
    &FCharacterInfoModel::DodgeRate,
    // ������
    &FCharacterInfoModel::HitRate,
    // ������
    &FCharacterInfoModel::CritRate,
};

int32 FInfoModelAccessHelper::GetPropertyValue(ECharacterPropertyType type) const
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    return InfoModel.*GetPropertyPtr(type);
}

void FInfoModelAccessHelper::SetPropertyValue(ECharacterPropertyType type, int32 value) const
{
    _ASSERT(static_cast<uint32>(type) < PropertySetCount);
    InfoModel.*GetPropertyPtr(type) = value;
}
