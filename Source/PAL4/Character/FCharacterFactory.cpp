// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterFactory.h"
#include "DataModel/IRoleDataProvider.h"
#include "DataModel/IMonsterDataProvider.h"
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

TSharedRef<IRoleProperty> FCharacterFactory::CreateRole(int32 id, int32 level, int32 experience) const
{
    if (!CharacterInherentInfos.Contains(id))
    {
        auto& basicData = RoleDataProvider->GetRoleBaseData(id);

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

    auto& roleData = RoleDataProvider->GetRoleLevelData(id, level);
    FCharacterBasicInfo basicInfo;
    basicInfo.Level = level;
    basicInfo.Experience = experience;
    // TODO: 使用存档数据
    basicInfo.HealthPoint = roleData.MaxHealthPoint;
}

TSharedRef<IMonsterProperty> FCharacterFactory::CreateMonster(int32 id) const
{
}
