#pragma once

#include <SharedPointer.h>

#include "../CharacterBridge/ICharacterBattleDelegate.h"
#include "FCharacterTemporaryStatus.h"
#include "FCharacterRoundManager.h"

class PAL4_API FBattleCharacter
{
public:
    explicit FBattleCharacter(const TSharedRef<ICharacterBattleDelegate>&);
    FBattleCharacter(FBattleCharacter&&) = default;

    FBattleCharacter& operator=(FBattleCharacter&&) = default;

    ICharacterBattleDelegate& GetCharacterDelegate() const { return CharacterDelegate.Get(); }
    FCharacterTemporaryStatus& GetTemporaryStatus() { return TemporaryStatus; }
    const FCharacterTemporaryStatus& GetTemporaryStatus() const { return TemporaryStatus; }
    FCharacterRoundManager& GetRoundManager() { return RoundManager; }
    const FCharacterRoundManager& GetRoundManager() const { return RoundManager; }

    void OnBattleBegin();
    void OnBattleFinished();

private:
    TSharedRef<ICharacterBattleDelegate> CharacterDelegate;
    FCharacterTemporaryStatus TemporaryStatus;
    FCharacterRoundManager RoundManager;
};
