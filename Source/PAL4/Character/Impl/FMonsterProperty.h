#pragma once

#include <SharedPointer.h>

#include "../IMonsterProperty.h"
#include "FCharacterPersistentStatus.h"


class PAL4_API FMonsterProperty : public IMonsterProperty
{
public:
    FMonsterProperty(const TSharedRef<FCharacterInherentInfo>&, const TSharedRef<FMonsterInherentInfo>&, const FCharacterBasicInfo&, const FCharacterStatusInfo&, const FMonsterTypicalInfo&);
    FMonsterProperty(const FMonsterProperty&) = default;
    FMonsterProperty(FMonsterProperty&&) = default;

    FMonsterProperty& operator=(const FMonsterProperty&) = default;
    FMonsterProperty& operator=(FMonsterProperty&&) = default;

    void UpdateStatusInfo(ECharacterStatusType, int32) override final;

    void UpdateStatusInfo(const FCharacterStatusInfo&) override final;

    const FCharacterInherentInfo& GetCharacterInherentInfo() const override final
    {
        return CharacterInherentInfo.Get();
    }

    ICharacterStatusProperty& StatusProperty() override final { return PersistentStatus; }

    const ICharacterStatusProperty& StatusProperty() const override final { return PersistentStatus; }

    const FMonsterInherentInfo& GetMonsterInherentInfo() const override final
    {
        return MonsterInherentInfo.Get();
    }

private:
    TSharedRef<FCharacterInherentInfo> CharacterInherentInfo;
    TSharedRef<FMonsterInherentInfo> MonsterInherentInfo;
    FCharacterStatusInfo StatusInfo;
    FCharacterPersistentStatus PersistentStatus;
};
