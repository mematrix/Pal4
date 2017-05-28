#pragma once

#include <Map.h>
#include <SharedPointer.h>

#include "Combat/Interface/Character/ICharacterTempStatusOperator.h"
#include "FTemporaryStatus.h"

class FCombatCharacter;
class ICharacterDelegate;
class IRoundManager;
class ITempStatusOpWrapper;


class PAL4_API FCharacterTempStatusManager : public ICharacterTempStatusOperator
{
public:
    explicit FCharacterTempStatusManager(ICharacterDelegate&);

    FCharacterTempStatusManager(const FCharacterTempStatusManager&) = default;
    FCharacterTempStatusManager(FCharacterTempStatusManager&&) = default;
    
    FCharacterTempStatusManager& operator=(const FCharacterTempStatusManager&) = default;
    FCharacterTempStatusManager& operator=(FCharacterTempStatusManager&&) = default;

    ICharacterDelegate& GetCharacter() { return Character; }
    const ICharacterDelegate& GetCharacter() const { return Character; }

    IRoundManager& GetRoundManager() override;
    inline const IRoundManager& GetRoundManager() const;

    void AddTemporaryStatus(ECharacterStatusType, const TSharedRef<ITempStatusOpWrapper>&) override;

    void RemoveTemporaryStatus(ECharacterStatusType, ITempStatusOpWrapper&) override;

    FTemporaryStatus& GetTempStatus() override;

private:
    ICharacterDelegate& Character;
    FTemporaryStatus TempStatus;
    TMap<int32, TSharedRef<ITempStatusOpWrapper>> StatusMap;
};
