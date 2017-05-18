// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterFactory.h"
#include "DataModel/IRoleDataProvider.h"
#include "DataModel/IMonsterDataProvider.h"
#include "DataModel/FGameArchive.h"
#include "FRoleProperty.h"
#include "FMonsterProperty.h"
#include "Primitives/Model/FCharacterInherentInfo.h"
#include "Primitives/Model/FMonsterInherentInfo.h"


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
        info->CraftIncreaseValue = basicData.CraftIncreaseValue;
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
    auto& basicData = MonsterDataProvider->GetMonsterData(id);

    if (!CharacterInherentInfos.Contains(id))
    {
        auto info = MakeShared<FCharacterInherentInfo>();
        info->ID = basicData.ID;
        info->Name = FName(UTF8_TO_TCHAR(basicData.Name.c_str()));
        info->Race = static_cast<ERace>(basicData.Race);
        info->PhysicalAttackTarget = static_cast<EPhysicalAttackTarget>(basicData.PhysicalAttackTarget);
        info->PhysicalAttackType = static_cast<EPhysicalAttackType>(basicData.PhysicalAttackType);
        info->CraftIncreaseValue = basicData.CraftIncreaseValue;
        info->IconID2D = basicData.IconID2D;
        info->MapID3D = basicData.MapID3D;
        info->ModelID3D = basicData.ModelID3D;
        info->InjuredSound1 = basicData.InjuredSound1;
        info->InjuredSound2 = basicData.InjuredSound2;
        info->InjuredSound3 = basicData.InjuredSound3;

        CharacterInherentInfos.Add(id, info);
    }

    if (!MonsterInherentInfos.Contains(id))
    {
        auto info = MakeShared<FMonsterInherentInfo>();
        info->Description = FName(UTF8_TO_TCHAR(basicData.Description.c_str()));
        info->IsBoss = basicData.IsBoss;
        info->AIType = static_cast<EAIType>(basicData.AIType);
        info->SkillIDList[0] = basicData.SkillID1;
        info->SkillIDList[1] = basicData.SkillID2;
        info->SkillIDList[2] = basicData.SkillID3;
        info->SkillIDList[3] = basicData.SkillID4;
        info->SkillIDList[4] = basicData.SkillID5;
        info->SkillIDList[5] = basicData.SkillID6;

        info->StealPropID = basicData.StealPropID;
        info->StealPropCount = basicData.StealPropCount;
        info->DropPropIDList[0] = basicData.DropPropID1;
        info->DropPropIDList[1] = basicData.DropPropID2;
        info->DropPropIDList[2] = basicData.DropPropID3;
        info->DropPropIDList[4] = basicData.DropPropID4;
        info->DropPropProbability[0] = basicData.DropPropProbability1;
        info->DropPropProbability[1] = basicData.DropPropProbability2;
        info->DropPropProbability[2] = basicData.DropPropProbability3;
        info->DropPropProbability[3] = basicData.DropPropProbability4;
        info->DropMoneyMinValue = basicData.DropMoneyMinValue;
        info->DropMoneyMaxValue = basicData.DropMoneyMaxValue;

        //info->CraftInitPoint = basicData.CraftInitPoint;
        info->ImmuneFlags = basicData.ImmuneFlags;
        info->DeathSound = basicData.DeathSound;

        MonsterInherentInfos.Add(id, info);
    }

    auto& inherentInfo = CharacterInherentInfos[id];
    auto& monsterInherentInfo = MonsterInherentInfos[id];

    FCharacterBasicInfo basicInfo;
    basicInfo.Level = basicData.Level;
    basicInfo.Experience = basicData.Experience;
    basicInfo.HealthPoint = basicData.MaxHealthPoint;
    basicInfo.ManaPoint = basicData.MaxManaPoint;
    basicInfo.CraftPoint = basicData.CraftInitPoint;
    basicInfo.MagicPoints[0] = basicData.WaterMagicPoint;
    basicInfo.MagicPoints[1] = basicData.FireMagicPoint;
    basicInfo.MagicPoints[2] = basicData.ThunderMagicPoint;
    basicInfo.MagicPoints[3] = basicData.WindMagicPoint;
    basicInfo.MagicPoints[4] = basicData.SoilMagicPoint;
    basicInfo.MaxHealthPoint = basicData.MaxHealthPoint;
    basicInfo.MaxManaPoint = basicData.MaxManaPoint;
    basicInfo.MaxCraftPoint = 100;

    FCharacterStatusInfo statusInfo;
    statusInfo.AttackPoint = basicData.AttackPoint;
    statusInfo.LuckPoint = basicData.LuckPoint;
    statusInfo.NimbusPoint = basicData.NimbusPoint;
    statusInfo.SpeedPoint = basicData.SpeedPoint;
    statusInfo.DefencePoint = basicData.DefencePoint;
    statusInfo.PhysicalDamageAttach = basicData.PhysicalDamageAttach;
    statusInfo.WaterElementalDamageAttach = basicData.WaterElementalDamageAttach;
    statusInfo.FireElementalDamageAttach = basicData.FireElementalDamageAttach;
    statusInfo.ThunderElementalDamageAttach = basicData.ThunderElementalDamageAttach;
    statusInfo.WindElementalDamageAttach = basicData.WindElementalDamageAttach;
    statusInfo.SoilElementalDamageAttach = basicData.SoilElementalDamageAttach;

    statusInfo.PhysicalResistance = basicData.PhysicalResistance;
    statusInfo.WaterMagicResistance = basicData.WaterMagicResistance;
    statusInfo.FireMagicResistance = basicData.FireMagicResistance;
    statusInfo.ThunderMagicResistance = basicData.ThunderMagicResistance;
    statusInfo.WindMagicResistance = basicData.WindMagicResistance;
    statusInfo.SoilMagicResistance = basicData.SoilMagicResistance;
    statusInfo.PhysicalDamageBounce = basicData.PhysicalDamageBounce;
    statusInfo.WaterElementalDamageBounce = basicData.WaterElementalDamageBounce;
    statusInfo.FireElementalDamageBounce = basicData.FireElementalDamageBounce;
    statusInfo.ThunderElementalDamageBounce = basicData.ThunderElementalDamageBounce;
    statusInfo.WindElementalDamageBounce = basicData.WindElementalDamageBounce;
    statusInfo.SoilElementalDamageBounce = basicData.SoilElementalDamageBounce;
    statusInfo.BlockRate = basicData.BlockRate;
    statusInfo.HitRate = basicData.HitRate;
    statusInfo.CritRate = basicData.CritRate;

    FMonsterTypicalInfo typicalInfo;
    typicalInfo.HitbackRate = basicData.HitbackRate;
    typicalInfo.ImmuneFlags = 0;

    return MakeShared<FMonsterProperty>(inherentInfo, monsterInherentInfo, basicInfo, statusInfo, typicalInfo);
}
