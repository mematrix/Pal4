// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FLevelManager.h"
#include "FCoreGame.h"
#include "Primitives/Property/IRoleProperty.h"
#include "Primitives/Model/FCharacterInherentInfo.h"
#include "Primitives/Model/FCharacterStatusInfo.h"
#include "DataModel/IDataProviderManager.h"
#include "DataModel/IRoleDataProvider.h"


void FLevelManager::AddRoleExperience(IRoleProperty& role, int32 exp)
{
    auto& game = FCoreGame::SharedInstance();
    auto& provider = game.GetDataProviderManager().GetRoleDataProvider();

    auto& info = role.GetBasicInfo();
    int32 id = role.GetCharacterInherentInfo().ID;

    int32 curExp = provider.GetLeastExperienceOfLevel(id, info.Level) + info.Experience;
    int32 newLevel = provider.ComputeLevelByExperience(id, curExp + exp);

    // Éý¼¶ÁË
    if (newLevel != info.Level)
    {
        int32 baseExp = provider.GetLeastExperienceOfLevel(id, newLevel);
        int32 restExp = curExp + exp - baseExp;
        auto& data = provider.GetRoleLevelData(id, newLevel);

        FCharacterBasicInfo basicInfo;
        basicInfo.Level = newLevel;
        basicInfo.Experience = restExp;
        basicInfo.MaxHealthPoint = data.MaxHealthPoint;
        basicInfo.MaxManaPoint = data.MaxManaPoint;
        basicInfo.MaxCraftPoint = 100;
        basicInfo.HealthPoint = data.MaxHealthPoint;
        basicInfo.ManaPoint = data.MaxManaPoint;
        basicInfo.CraftPoint = info.CraftPoint;
        basicInfo.MagicPoints[0] = data.WaterMagicPoint + info.MagicPoints[0];
        basicInfo.MagicPoints[1] = data.FireMagicPoint + info.MagicPoints[1];
        basicInfo.MagicPoints[2] = data.ThunderMagicPoint + info.MagicPoints[2];
        basicInfo.MagicPoints[3] = data.WindMagicPoint + info.MagicPoints[3];
        basicInfo.MagicPoints[4] = data.SoilMagicPoint + info.MagicPoints[4];
        role.SetBasicInfo(basicInfo);

        FCharacterStatusInfo statusInfo;
        statusInfo.AttackPoint = data.AttackPoint;
        statusInfo.LuckPoint = data.LuckPoint;
        statusInfo.NimbusPoint = data.NimbusPoint;
        statusInfo.SpeedPoint = data.SpeedPoint;
        statusInfo.DefencePoint = data.DefencePoint;
        statusInfo.PhysicalDamageAttach = data.PhysicalDamageAttach;
        statusInfo.WaterElementalDamageAttach = data.WaterElementalDamageAttach;
        statusInfo.FireElementalDamageAttach = data.FireElementalDamageAttach;
        statusInfo.ThunderElementalDamageAttach = data.ThunderElementalDamageAttach;
        statusInfo.WindElementalDamageAttach = data.WindElementalDamageAttach;
        statusInfo.SoilElementalDamageAttach = data.SoilElementalDamageAttach;
        statusInfo.PhysicalResistance = data.PhysicalResistance;
        statusInfo.WaterMagicResistance = data.WaterMagicResistance;
        statusInfo.FireMagicResistance = data.FireMagicResistance;
        statusInfo.ThunderMagicResistance = data.ThunderMagicResistance;
        statusInfo.WindMagicResistance = data.WindMagicResistance;
        statusInfo.SoilMagicResistance = data.SoilMagicResistance;
        statusInfo.PhysicalDamageBounce = data.PhysicalDamageBounce;
        statusInfo.WaterElementalDamageBounce = data.WaterElementalDamageBounce;
        statusInfo.FireElementalDamageBounce = data.FireElementalDamageBounce;
        statusInfo.ThunderElementalDamageBounce = data.ThunderElementalDamageBounce;
        statusInfo.WindElementalDamageBounce = data.WindElementalDamageBounce;
        statusInfo.SoilElementalDamageBounce = data.SoilElementalDamageBounce;
        statusInfo.BlockRate = data.BlockRate;
        statusInfo.HitRate = data.HitRate;
        statusInfo.CritRate = data.CritRate;
        role.UpdateStatusInfo(statusInfo);
    }
    else
    {
        role.SetBasicInfo(ECharacterBasicType::Experience, curExp + exp);
    }
}
