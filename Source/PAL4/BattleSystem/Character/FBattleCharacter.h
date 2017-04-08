#pragma once

#include <SharedPointer.h>

#include "../CharacterBridge/ICharacterBattleDelegate.h"
#include "FCharacterTemporaryStatus.h"
#include "FCharacterRoundManager.h"

class PAL4_API FBattleCharacter
{
public:
    explicit FBattleCharacter(const TSharedRef<ICharacterBattleDelegate>&);

    ICharacterBattleDelegate& GetCharacterDelegate() const { return CharacterDelegate.Get(); }
    FCharacterTemporaryStatus& GetTemporaryStatus() { return TemporaryStatus; }
    FCharacterRoundManager& GetRoundManager() { return RoundManager; }

private:
    TSharedRef<ICharacterBattleDelegate> CharacterDelegate;
    FCharacterTemporaryStatus TemporaryStatus;
    FCharacterRoundManager RoundManager;
};
