#pragma once

#include <Map.h>
#include <SharedPointer.h>

#include "Combat/Interface/Character/IStatusManager.h"
#include "FTemporaryStatus.h"

class FCombatCharacter;
class ICharacterDelegate;
class IRoundManager;
class ITempStatusOpWrapper;


class PAL4_API FStatusManager : public IStatusManager
{
public:
    explicit FStatusManager(ICharacterDelegate&);

    FStatusManager(const FStatusManager&) = default;
    FStatusManager(FStatusManager&&) = default;
    
    FStatusManager& operator=(const FStatusManager&) = default;
    FStatusManager& operator=(FStatusManager&&) = default;

    ICharacterDelegate& GetCharacter() { return Character; }
    const ICharacterDelegate& GetCharacter() const { return Character; }

private:
    ICharacterDelegate& Character;
    FTemporaryStatus TempStatus;
    TMap<int32, TSharedRef<ITempStatusOpWrapper>> StatusMap;
};
