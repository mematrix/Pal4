#pragma once

#include <Map.h>
#include <SharedPointer.h>

#include "ITempStatusOpWrapper.h"


class PAL4_API FCharacterTempStatusManager
{
public:
    explicit FCharacterTempStatusManager(FBattleCharacter&);

private:
    FBattleCharacter& TemporaryStatus;
    TMap<int32, TSharedRef<ITempStatusOpWrapper>> StatusMap;
};
