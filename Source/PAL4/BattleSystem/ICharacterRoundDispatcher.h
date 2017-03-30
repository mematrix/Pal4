#pragma once

#include <Array.h>
#include <SharedPointer.h>

#include "IBattleStatus.h"

class PAL4_API ICharacterRoundDispatcher
{
public:
    virtual const TSharedRef<IBattleStatus>& MoveToNext(const TArray<TSharedRef<IBattleStatus>>&) = 0;
};
