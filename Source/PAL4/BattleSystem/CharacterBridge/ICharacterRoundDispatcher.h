#pragma once

#include <Array.h>
#include <SharedPointer.h>

#include "ICharacterBattleDelegate.h"

class PAL4_API ICharacterRoundDispatcher
{
public:
    virtual ~ICharacterRoundDispatcher()
    {
    }

    virtual const TSharedRef<ICharacterBattleStatus>& MoveToNext(const TArray<TSharedRef<ICharacterBattleStatus>>&) = 0;
};
