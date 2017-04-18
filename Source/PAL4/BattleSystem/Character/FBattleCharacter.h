#pragma once

#include <SharedPointer.h>

#include "../CharacterBridge/ICharacterBattleDelegate.h"
#include "FCharacterTemporaryStatus.h"
#include "FCharacterRoundManager.h"
#include "FCharacterTempStatusManager.h"
#include "FPassiveActionInterceptor.h"

class PAL4_API FBattleCharacter
{
public:
    explicit FBattleCharacter(const TSharedRef<ICharacterBattleDelegate>&);
    FBattleCharacter(FBattleCharacter&&) = default;

    FBattleCharacter& operator=(FBattleCharacter&&) = default;

    ICharacterBattleDelegate& GetCharacterDelegate() const { return CharacterDelegate.Get(); }

    ICharacterPropertyManager& GetPropertyManager() { return CharacterDelegate->GetPropertyManager(); }

    FPassiveActionInterceptor& GetActionInterceptor() { return ActionInterceptor; }

    FCharacterTemporaryStatus& GetTemporaryStatus() { return TemporaryStatus; }
    const FCharacterTemporaryStatus& GetTemporaryStatus() const { return TemporaryStatus; }

    FCharacterRoundManager& GetRoundManager() { return RoundManager; }
    const FCharacterRoundManager& GetRoundManager() const { return RoundManager; }

    FCharacterTempStatusManager& GetTempStatusManager() { return TempStatusManager; }
    const FCharacterTempStatusManager& GetTempStatusManager() const { return TempStatusManager; }

    void OnBattleBegin();
    void OnBattleFinished();

private:
    TSharedRef<ICharacterBattleDelegate> CharacterDelegate;
    FCharacterTemporaryStatus TemporaryStatus;
    FCharacterRoundManager RoundManager;
    FCharacterTempStatusManager TempStatusManager;
    FPassiveActionInterceptor ActionInterceptor;
};
