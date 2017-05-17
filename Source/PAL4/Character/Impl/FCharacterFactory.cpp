// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterFactory.h"
#include "DataModel/IRoleDataProvider.h"
#include "DataModel/IMonsterDataProvider.h"
#include "DataModel/FGameArchive.h"
#include "FRoleProperty.h"
#include "FMonsterProperty.h"
#include "Primitives/Model/FCharacterInherentInfo.h"


FCharacterFactory::FCharacterFactory(const TSharedRef<IRoleDataProvider>& role, const TSharedRef<IMonsterDataProvider>& monster)
    : RoleDataProvider(role),
    MonsterDataProvider(monster),
    CharacterInherentInfos(),
    MonsterInherentInfos()
{
}

TSharedRef<IRoleProperty> FCharacterFactory::CreateRole(int32 id, const FCharacterArchive& archive) const
{
    auto& basicData = RoleDataProvider->GetRoleBaseData(id);

    if (!CharacterInherentInfos.Contains(id))
    {
        auto info = MakeShared<FCharacterInherentInfo>();
        info->ID = basicData.ID;
        info->Name = FName(UTF8_TO_TCHAR(basicData.Name.c_str()));
        info->Race = static_cast<ERace>(basicData.Race);
        info->PhysicalAttackTarget = static_cast<EPhysicalAttackTarget>(basicData.PhysicalAttackTarget);
        info->PhysicalAttackType = static_cast<EPhysicalAttackType>(basicData.PhysicalAttackType);
        info->IconID2D = basicData.IconID2D;
        info->MapID3D = basicData.MapID3D;
        info->ModelID3D = basicData.ModelID3D;
        info->InjuredSound1 = basicData.InjuredSound1;
        info->InjuredSound2 = basicData.InjuredSound2;
        info->InjuredSound3 = basicData.InjuredSound3;

        CharacterInherentInfos.Add(id, info);
    }

    auto& inherentInfo = CharacterInherentInfos[id];

    auto& roleData = RoleDataProvider->GetRoleLevelData(id, archive.Level);

    FCharacterBasicInfo basicInfo;
    basicInfo.Level = archive.Level;
    basicInfo.Experience = archive.Experience;
    basicInfo.HealthPoint = archive.HealthPoint;
    basicInfo.ManaPoint = archive.ManaPoint;
    basicInfo.CraftPoint = archive.CraftPoint;
    for (int i = 0; i < 5; ++i)
    {
        basicInfo.MagicPoints[i] = archive.MagicPoints[i];
    }
    basicInfo.MaxHealthPoint = roleData.MaxHealthPoint;
    basicInfo.MaxManaPoint = roleData.MaxManaPoint;
    basicInfo.MaxCraftPoint = 100;

    FCharacterStatusInfo statusInfo;
    statusInfo.AttackPoint = roleData.AttackPoint;
    statusInfo.LuckPoint = roleData.LuckPoint;
    statusInfo.NimbusPoint = roleData.NimbusPoint;
    statusInfo.SpeedPoint = roleData.SpeedPoint;
    statusInfo.DefencePoint = roleData.DefencePoint;
    statusInfo.PhysicalDamageAttach = roleData.PhysicalDamageAttach;
    statusInfo.WaterElementalDamageAttach = roleData.WaterElementalDamageAttach;
    statusInfo.FireElementalDamageAttach = roleData.FireElementalDamageAttach;
    statusInfo.ThunderElementalDamageAttach = roleData.ThunderElementalDamageAttach;
    statusInfo.WindElementalDamageAttach = roleData.WindElementalDamageAttach;
    statusInfo.SoilElementalDamageAttach = roleData.SoilElementalDamageAttach;

    statusInfo.PhysicalResistance = roleData.PhysicalResistance;
    statusInfo.WaterMagicResistance = roleData.WaterMagicResistance;
    statusInfo.FireMagicResistance = roleData.FireMagicResistance;
    statusInfo.ThunderMagicResistance = roleData.ThunderMagicResistance;
    statusInfo.WindMagicResistance = roleData.WindMagicResistance;
    statusInfo.SoilMagicResistance = roleData.SoilMagicResistance;
    statusInfo.PhysicalDamageBounce = roleData.PhysicalDamageBounce;
    statusInfo.WaterElementalDamageBounce = roleData.WaterElementalDamageBounce;
    statusInfo.FireElementalDamageBounce = roleData.FireElementalDamageBounce;
    statusInfo.ThunderElementalDamageBounce = roleData.ThunderElementalDamageBounce;
    statusInfo.WindElementalDamageBounce = roleData.WindElementalDamageBounce;
    statusInfo.SoilElementalDamageBounce = roleData.SoilElementalDamageBounce;
    statusInfo.BlockRate = roleData.BlockRate;
    statusInfo.HitRate = roleData.HitRate;
    statusInfo.CritRate = roleData.CritRate;

    return MakeShared<FRoleProperty>(inherentInfo, basicInfo, statusInfo, archive.Favors, basicData.InitMagicPoint);
}

TSharedRef<IMonsterProperty> FCharacterFactory::CreateMonster(int32 id) const
{
}
