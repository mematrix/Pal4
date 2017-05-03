#pragma once

#include <SharedPointer.h>

class ICharacterCombatDelegate;


class PAL4_API ICharacterRoundDispatcher
{
public:
    virtual ~ICharacterRoundDispatcher()
    {
    }

    virtual void Init(const TArray<TSharedRef<ICharacterCombatDelegate>>&) = 0;

    virtual void OnBattleBegin() = 0;

    virtual void AddCharacter(const TSharedRef<ICharacterCombatDelegate>&) = 0;

    virtual ICharacterCombatDelegate& MoveToNext() = 0;

    virtual void OnBattleFinished() = 0;
};
