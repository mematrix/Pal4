#pragma once

#include <Map.h>

#include "../ICharacterFactory.h"


class IRoleDataProvider;
class IMonsterDataProvider;
struct FCharacterInherentInfo;
struct FMonsterInherentInfo;


class PAL4_API FCharacterFactory : public ICharacterFactory
{
public:
    explicit FCharacterFactory(const TSharedRef<IRoleDataProvider>&, const TSharedRef<IMonsterDataProvider>&);

    TSharedRef<IRoleProperty> CreateRole(int32 id, const FCharacterArchive& archive) const override;

    TSharedRef<IMonsterProperty> CreateMonster(int32 id) const override;

private:
    TSharedRef<IRoleDataProvider> RoleDataProvider;
    TSharedRef<IMonsterDataProvider> MonsterDataProvider;
    mutable TMap<int32, TSharedRef<FCharacterInherentInfo>> CharacterInherentInfos;
    mutable TMap<int32, TSharedRef<FMonsterInherentInfo>> MonsterInherentInfos;
};
