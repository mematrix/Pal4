// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <crtdbg.h>

#include "FStatusInfoAccessHelper.h"
#include "../Model/FCharacterStatusInfo.h"

int32 FCharacterStatusInfo::* const FStatusInfoAccessHelper::PropertySet[PropertySetCount] =
{
    // 武
    &FCharacterStatusInfo::AttackPoint,
    // 运
    &FCharacterStatusInfo::LuckPoint,
    // 灵
    &FCharacterStatusInfo::NimbusPoint,
    // 速
    &FCharacterStatusInfo::SpeedPoint,
    // 防
    &FCharacterStatusInfo::DefencePoint,

    // 物理抗性
    &FCharacterStatusInfo::AttackResistance,
    // 水系仙术抗性
    &FCharacterStatusInfo::WaterMagicResistance,
    // 火系仙术抗性
    &FCharacterStatusInfo::FireMagicResistance,
    // 雷系仙术抗性
    &FCharacterStatusInfo::ThunderMagicResistance,
    // 风系仙术抗性
    &FCharacterStatusInfo::WindMagicResistance,
    // 土系仙术抗性
    &FCharacterStatusInfo::SoilMagicResistance,

    // 直接物理伤害
    &FCharacterStatusInfo::DirectAttackDamage,
    // 水系元素伤害
    &FCharacterStatusInfo::WaterElementalDamage,
    // 火系元素伤害
    &FCharacterStatusInfo::FireElementalDamage,
    // 雷系元素伤害
    &FCharacterStatusInfo::ThunderElementalDamage,
    // 风系元素伤害
    &FCharacterStatusInfo::WindElementalDamage,
    // 土系元素伤害
    &FCharacterStatusInfo::SoilElementalDamage,

    // 元素伤害抗性
    &FCharacterStatusInfo::ElementalResistance,

    // 格挡率
    &FCharacterStatusInfo::BlockRate,
    // 闪避率
    &FCharacterStatusInfo::DodgeRate,
    // 命中率
    &FCharacterStatusInfo::HitRate,
    // 暴击率
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
