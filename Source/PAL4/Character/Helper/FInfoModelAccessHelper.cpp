// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <crtdbg.h>

#include "FInfoModelAccessHelper.h"
#include "../Model/FCharacterInfoModel.h"

int32 FCharacterInfoModel::* const FInfoModelAccessHelper::PropertySet[PropertySetCount] =
{
    // 武
    &FCharacterInfoModel::AttackPoint,
    // 运
    &FCharacterInfoModel::LuckPoint,
    // 灵
    &FCharacterInfoModel::NimbusPoint,
    // 速
    &FCharacterInfoModel::SpeedPoint,
    // 防
    &FCharacterInfoModel::DefencePoint,

    // 物理抗性
    &FCharacterInfoModel::AttackResistance,
    // 水系仙术抗性
    &FCharacterInfoModel::WaterMagicResistance,
    // 火系仙术抗性
    &FCharacterInfoModel::FireMagicResistance,
    // 雷系仙术抗性
    &FCharacterInfoModel::ThunderMagicResistance,
    // 风系仙术抗性
    &FCharacterInfoModel::WindMagicResistance,
    // 土系仙术抗性
    &FCharacterInfoModel::SoilMagicResistance,

    // 直接物理伤害
    &FCharacterInfoModel::DirectAttackDamage,
    // 水系元素伤害
    &FCharacterInfoModel::WaterElementalDamage,
    // 火系元素伤害
    &FCharacterInfoModel::FireElementalDamage,
    // 雷系元素伤害
    &FCharacterInfoModel::ThunderElementalDamage,
    // 风系元素伤害
    &FCharacterInfoModel::WindElementalDamage,
    // 土系元素伤害
    &FCharacterInfoModel::SoilElementalDamage,

    // 元素伤害抗性
    &FCharacterInfoModel::ElementalResistance,

    // 格挡率
    &FCharacterInfoModel::BlockRate,
    // 闪避率
    &FCharacterInfoModel::DodgeRate,
    // 命中率
    &FCharacterInfoModel::HitRate,
    // 暴击率
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
