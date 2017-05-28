#pragma once

#include <SharedPointer.h>

class ICharacterDelegate;


class PAL4_API IRoundDispatcher
{
public:
    virtual ~IRoundDispatcher()
    {
    }

    virtual void Init(const TArray<TSharedRef<ICharacterDelegate>>&) = 0;

    virtual void OnBattleBegin() = 0;

    virtual void AddCharacter(const TSharedRef<ICharacterDelegate>&) = 0;

    virtual ICharacterDelegate& MoveToNext() = 0;

    virtual void OnBattleFinished() = 0;
};
