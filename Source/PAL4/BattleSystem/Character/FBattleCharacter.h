#pragma once

#include <SharedPointer.h>

#include "../CharacterBridge/ICharacterBattleContext.h"
#include "../CharacterBridge/ICharacterBattleDelegate.h"
#include "FCharacterRoundManager.h"
#include "FCharacterTempStatusManager.h"
#include "FPassiveActionInterceptor.h"

class PAL4_API FBattleCharacter : public ICharacterBattleContext
{
public:
    explicit FBattleCharacter(const TSharedRef<ICharacterBattleDelegate>&);
    FBattleCharacter(FBattleCharacter&&) = default;

    FBattleCharacter& operator=(FBattleCharacter&&) = default;

    ICharacterBattleDelegate& GetCharacterDelegate() const { return CharacterDelegate.Get(); }

    ICharacterPropertyManager& GetPropertyManager() const { return CharacterDelegate->GetPropertyManager(); }

    FPassiveActionInterceptor& GetActionInterceptor() override { return ActionInterceptor; }

    FCharacterTempStatusManager& GetTempStatusAccessor() override { return TempStatusManager; }

    FCharacterRoundManager& GetRoundManager() override { return RoundManager; }
    const FCharacterRoundManager& GetRoundManager() const { return RoundManager; }

    FCharacterTempStatusManager& GetTempStatusManager() { return TempStatusManager; }
    const FCharacterTempStatusManager& GetTempStatusManager() const { return TempStatusManager; }

    void OnBattleBegin();
    void OnBattleFinished();

private:
    TSharedRef<ICharacterBattleDelegate> CharacterDelegate;
    FCharacterRoundManager RoundManager;
    FCharacterTempStatusManager TempStatusManager;
    FPassiveActionInterceptor ActionInterceptor;
};
