#pragma once

#include <Array.h>
#include <SharedPointer.h>
#include "../Character/FBattleCharacter.h"


class PAL4_API ICharacterRoundDispatcher
{
public:
    virtual ~ICharacterRoundDispatcher()
    {
    }

    virtual void OnBattleBegin(const TArray<TSharedRef<FBattleCharacter>>&) = 0;

    virtual void AddCharacter(const TSharedRef<FBattleCharacter>&) = 0;

    virtual FBattleCharacter& MoveToNext() = 0;

    virtual void OnBattleFinished() = 0;
};
