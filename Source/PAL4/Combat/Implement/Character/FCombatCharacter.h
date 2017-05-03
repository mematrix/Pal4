#pragma once

#include <SharedPointer.h>

#include "CombatDelegate/Character/ICharacterCombatContext.h"
#include "CombatDelegate/Character/ICharacterCombatDelegate.h"
#include "FCharacterRoundManager.h"
#include "FCharacterTempStatusManager.h"
#include "FPassiveActionInterceptor.h"


class PAL4_API FCombatCharacter : public ICharacterCombatContext
{
public:
    explicit FCombatCharacter(const TSharedRef<ICharacterCombatDelegate>&);
    FCombatCharacter(FCombatCharacter&&) = default;

    FCombatCharacter& operator=(FCombatCharacter&&) = default;

    ICharacterCombatDelegate& GetCharacterDelegate() const { return CharacterDelegate.Get(); }

    ICharacterPropertyManager& GetPropertyManager() const { return CharacterDelegate->GetPropertyManager(); }

    FPassiveActionInterceptor& GetActionInterceptor() override { return ActionInterceptor; }

    FCharacterTemporaryStatus& GetTempStatus() override { return TempStatusManager.GetTempStatus(); }

    FCharacterRoundManager& GetRoundManager() override { return RoundManager; }
    const FCharacterRoundManager& GetRoundManager() const { return RoundManager; }

    FCharacterTempStatusManager& GetTempStatusManager() { return TempStatusManager; }
    const FCharacterTempStatusManager& GetTempStatusManager() const { return TempStatusManager; }

    void OnBattleBegin();
    void OnBattleFinished();

private:
    TSharedRef<ICharacterCombatDelegate> CharacterDelegate;
    FCharacterRoundManager RoundManager;
    FCharacterTempStatusManager TempStatusManager;
    FPassiveActionInterceptor ActionInterceptor;
};
