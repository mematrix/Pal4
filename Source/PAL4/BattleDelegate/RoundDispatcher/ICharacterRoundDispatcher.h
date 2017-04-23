#pragma once

#include <SharedPointer.h>

class ICharacterBattleDelegate;


class PAL4_API ICharacterRoundDispatcher
{
public:
    virtual ~ICharacterRoundDispatcher()
    {
    }

    virtual void OnBattleBegin(const TArray<TSharedRef<ICharacterBattleDelegate>>&) = 0;

    virtual void AddCharacter(const TSharedRef<ICharacterBattleDelegate>&) = 0;

    virtual ICharacterBattleDelegate& MoveToNext() = 0;

    virtual void OnBattleFinished() = 0;
};
