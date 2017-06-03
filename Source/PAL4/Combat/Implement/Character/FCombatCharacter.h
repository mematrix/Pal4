#pragma once

#include <SharedPointer.h>

#include "Combat/Interface/Character/ICombatContext.h"
#include "Combat/Interface/Character/ICharacterDelegate.h"
#include "FRoundManager.h"
#include "FStatusManager.h"
#include "FSkillReactor.h"


class PAL4_API FCombatCharacter : public ICombatContext
{
public:
    explicit FCombatCharacter(const TSharedRef<ICharacterDelegate>&);
    FCombatCharacter(FCombatCharacter&&) = default;

    FCombatCharacter& operator=(FCombatCharacter&&) = default;

    ICharacterDelegate& GetCharacterDelegate() const { return CharacterDelegate.Get(); }

    //IPropertyManager& GetPropertyManager() const { return CharacterDelegate->GetPropertyManager(); }

    FSkillReactor& GetSkillReactor() override { return ActionInterceptor; }

    FTemporaryStatus& GetTempStatus() override { return TempStatusManager.GetTempStatus(); }

    FRoundManager& GetRoundManager() override { return RoundManager; }
    const FRoundManager& GetRoundManager() const { return RoundManager; }

    FStatusManager& GetTempStatusManager() { return TempStatusManager; }
    const FStatusManager& GetTempStatusManager() const { return TempStatusManager; }

    void OnBattleBegin();
    void OnBattleFinished();

private:
    TSharedRef<ICharacterDelegate> CharacterDelegate;
    FRoundManager RoundManager;
    FStatusManager TempStatusManager;
    FSkillReactor ActionInterceptor;
};
