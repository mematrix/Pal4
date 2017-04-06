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

    virtual const TSharedRef<ICharacterBattleDelegate>& MoveToNext(const TArray<TSharedRef<ICharacterBattleDelegate>>&) = 0;
};
