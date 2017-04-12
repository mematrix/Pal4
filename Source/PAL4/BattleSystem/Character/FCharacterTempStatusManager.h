#pragma once

#include <Map.h>
#include <SharedPointer.h>

#include "ITempStatusOpWrapper.h"
#include "FCharacterTempStatusFacade.h"
#include "CharacterPrimitives/Model/ECharacterStatusType.h"

class FBattleCharacter;
class ICharacterBattleDelegate;
class ICharacterRoundManager;


class PAL4_API FCharacterTempStatusManager
{
public:
    explicit FCharacterTempStatusManager(FBattleCharacter&);

    FCharacterTempStatusFacade& GetTempStatusFacade() { return TempStatusFacade; }
    const FCharacterTempStatusFacade& GetTempStatusFacade() const { return TempStatusFacade; }

    inline ICharacterBattleDelegate& GetCharacter();
    inline const ICharacterBattleDelegate& GetCharacter() const;

    inline ICharacterRoundManager& GetRoundManager();
    inline const ICharacterRoundManager& GetRoundManager() const;

    void AddTemporaryStatus(ECharacterStatusType, const TSharedRef<ITempStatusOpWrapper>&);
    void RemoveTemporaryStatus(ECharacterStatusType, const ITempStatusOpWrapper&);

private:
    FBattleCharacter& Character;
    FCharacterTempStatusFacade TempStatusFacade;
    TMap<int32, TSharedRef<ITempStatusOpWrapper>> StatusMap;
};
