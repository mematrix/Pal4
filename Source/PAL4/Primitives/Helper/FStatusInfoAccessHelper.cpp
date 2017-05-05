// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <crtdbg.h>

#include "FStatusInfoAccessHelper.h"
#include "../Model/FCharacterStatusInfo.h"


int32 FCharacterStatusInfo::* const PropertySet[PropertySetCount] =
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

    // 直接物理伤害附加
    &FCharacterStatusInfo::PhysicalDamageAttach,
    // 水系元素伤害附加
    &FCharacterStatusInfo::WaterElementalDamageAttach,
    // 火系元素伤害附加
    &FCharacterStatusInfo::FireElementalDamageAttach,
    // 雷系元素伤害附加
    &FCharacterStatusInfo::ThunderElementalDamageAttach,
    // 风系元素伤害附加
    &FCharacterStatusInfo::WindElementalDamageAttach,
    // 土系元素伤害附加
    &FCharacterStatusInfo::SoilElementalDamageAttach,

    // 物理抗性
    &FCharacterStatusInfo::PhysicalResistance,
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

    // 物理伤害反弹
    &FCharacterStatusInfo::PhysicalDamageBounce,
    // 水属性伤害反弹
    &FCharacterStatusInfo::WaterElementalDamageBounce,
    // 火属性伤害反弹
    &FCharacterStatusInfo::FireElementalDamageBounce,
    // 雷属性伤害反弹
    &FCharacterStatusInfo::ThunderElementalDamageBounce,
    // 风属性伤害反弹
    &FCharacterStatusInfo::WindElementalDamageBounce,
    // 土属性伤害反弹
    &FCharacterStatusInfo::SoilElementalDamageBounce,

    // 格挡率
    &FCharacterStatusInfo::BlockRate,
    // 命中率
    &FCharacterStatusInfo::HitRate,
    // 暴击率
    &FCharacterStatusInfo::CritRate //,
    // 闪避率
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
