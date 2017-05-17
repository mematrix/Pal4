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

    const FCharacterInherentInfo& GetCharacterInherentInfo() const override;
    ICharacterStatusProperty& StatusProperty() override;
    const ICharacterStatusProperty& StatusProperty() const override;
    const FMonsterInherentInfo& GetMonsterInherentInfo() const override;

private:
    TSharedRef<FCharacterInherentInfo> CharacterInherentInfo;
    TSharedRef<FMonsterInherentInfo> MonsterInherentInfo;

};
