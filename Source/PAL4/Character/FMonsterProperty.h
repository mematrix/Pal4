#pragma once

#include <SharedPointer.h>

#include "Primitives/Property/IMonsterProperty.h"
#include "FCharacterPersistentStatus.h"


class PAL4_API FMonsterProperty : public IMonsterProperty
{
public:


    const FCharacterInherentInfo& GetCharacterInherentInfo() const override;
    ICharacterStatusProperty& StatusProperty() override;
    const ICharacterStatusProperty& StatusProperty() const override;
    const FMonsterInherentInfo& GetMonsterInherentInfo() const override;

private:
    TSharedRef<FCharacterInherentInfo> CharacterInherentInfo;
    TSharedRef<FMonsterInherentInfo> MonsterInherentInfo;

};
