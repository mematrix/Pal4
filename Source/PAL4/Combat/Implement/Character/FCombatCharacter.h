#pragma once

#include <SharedPointer.h>

#include "Combat/Interface/Character/ICharacterCombatContext.h"
#include "Combat/Interface/Character/ICharacterCombatDelegate.h"
#include "FRoundManager.h"
#include "FCharacterTempStatusManager.h"
#include "FPassiveActionInterceptor.h"


class PAL4_API FCombatCharacter : public ICharacterCombatContext
{
public:
    explicit FCombatCharacter(const TSharedRef<ICharacterCombatDelegate>&);
    FCombatCharacter(FCombatCharacter&&) = default;

    FCombatCharacter& operator=(FCombatCharacter&&) = default;

    ICharacterCombatDelegate& GetCharacterDelegate() const { return CharacterDelegate.Get(); }

    //IPropertyManager& GetPropertyManager() const { return CharacterDelegate->GetPropertyManager(); }

    FPassiveActionInterceptor& GetActionInterceptor() override { return ActionInterceptor; }

    FTemporaryStatus& GetTempStatus() override { return TempStatusManager.GetTempStatus(); }

    FRoundManager& GetRoundManager() override { return RoundManager; }
    const FRoundManager& GetRoundManager() const { return RoundManager; }

    FCharacterTempStatusManager& GetTempStatusManager() { return TempStatusManager; }
    const FCharacterTempStatusManager& GetTempStatusManager() const { return TempStatusManager; }

    void OnBattleBegin();
    void OnBattleFinished();

private:
    TSharedRef<ICharacterCombatDelegate> CharacterDelegate;
    FRoundManager RoundManager;
    FCharacterTempStatusManager TempStatusManager;
    FPassiveActionInterceptor ActionInterceptor;
};
