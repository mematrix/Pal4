#pragma once

#include <SharedPointer.h>
#include <Map.h>

class IRoleProperty;
class IMonsterProperty;
class IRoleDataProvider;
class IMonsterDataProvider;
class FCharacterInherentInfo;
class FMonsterInherentInfo;


class PAL4_API FCharacterFactory
{
public:
    explicit FCharacterFactory(const TSharedRef<IRoleDataProvider>&, const TSharedRef<IMonsterDataProvider>&);

    TSharedRef<IRoleProperty> CreateRole(int32 id, int32 level, int32 experience) const;

    TSharedRef<IMonsterProperty> CreateMonster(int32 id) const;

private:
    TSharedRef<IRoleDataProvider> RoleDataProvider;
    TSharedRef<IMonsterDataProvider> MonsterDataProvider;
    mutable TMap<int32, TSharedRef<FCharacterInherentInfo>> CharacterInherentInfos;
    mutable TMap<int32, TSharedRef<FMonsterInherentInfo>> MonsterInherentInfos;
};
