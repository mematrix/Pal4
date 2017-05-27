#pragma once

#include <Map.h>
#include <SharedPointer.h>

#include "Combat/Interface/Character/ICharacterTempStatusOperator.h"
#include "FCharacterTemporaryStatus.h"

class FCombatCharacter;
class ICharacterCombatDelegate;
class IRoundManager;
class ITempStatusOpWrapper;


class PAL4_API FCharacterTempStatusManager : public ICharacterTempStatusOperator
{
public:
    explicit FCharacterTempStatusManager(ICharacterCombatDelegate&);

    FCharacterTempStatusManager(const FCharacterTempStatusManager&) = default;
    FCharacterTempStatusManager(FCharacterTempStatusManager&&) = default;
    
    FCharacterTempStatusManager& operator=(const FCharacterTempStatusManager&) = default;
    FCharacterTempStatusManager& operator=(FCharacterTempStatusManager&&) = default;

    ICharacterCombatDelegate& GetCharacter() { return Character; }
    const ICharacterCombatDelegate& GetCharacter() const { return Character; }

    IRoundManager& GetRoundManager() override;
    inline const IRoundManager& GetRoundManager() const;

    void AddTemporaryStatus(ECharacterStatusType, const TSharedRef<ITempStatusOpWrapper>&) override;

    void RemoveTemporaryStatus(ECharacterStatusType, ITempStatusOpWrapper&) override;

    FCharacterTemporaryStatus& GetTempStatus() override;

private:
    ICharacterCombatDelegate& Character;
    FCharacterTemporaryStatus TempStatus;
    TMap<int32, TSharedRef<ITempStatusOpWrapper>> StatusMap;
};
