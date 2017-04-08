#pragma once

#include <SharedPointer.h>

#include "../CharacterBridge/ICharacterBattleDelegate.h"
#include "FCharacterTemporaryStatus.h"

class PAL4_API FBattleCharacter
{
public:
    explicit FBattleCharacter(const TSharedRef<ICharacterBattleDelegate>&);

private:
    TSharedRef<ICharacterBattleDelegate> CharacterDelegate;
    FCharacterTemporaryStatus TemporaryStatus;
};
