#pragma once

#include "Combat/Interface/Character/ICharacterCombatDelegate.h"
#include "Combat/Interface/Character/ICharacterCombatContext.h"
#include "Combat/Interface/Character/ITemporaryStatus.h"
#include "Primitives/Model/FCharacterStatusInfo.h"
#include "Primitives/Model/FCharacterInherentInfo.h"
#include "Character/Util/FCharacterHelper.h"


class PAL4_API FCharacterRoundInfo
{
public:
    FCharacterRoundInfo(ICharacterCombatDelegate& character, int32 position) :
        Character(character),
        CurrentPosition(position)
    {
    }

    int32 GetCurrentPosition() const { return CurrentPosition; }
    void SetCurrentPosition(int32 value) { CurrentPosition = value; }
    void AddCurrentPosition(int32 value) { CurrentPosition += value; }

    ICharacterCombatDelegate& GetCharacter() { return Character; }
    const ICharacterCombatDelegate& GetCharacter() const { return Character; }

    uint32 GetSpeedValue() const
    {
        return static_cast<uint32>(Character.GetContext()->GetTempStatus().GetAccumulatedInfo().SpeedPoint);
    }

    bool IsAlive() const
    {
        return FCharacterHelper::IsAlive(Character.GetProperty());
    }

    int32 GetCharacterId() const
    {
        return Character.GetProperty().GetCharacterInherentInfo().ID;
    }

private:
    ICharacterCombatDelegate& Character;
    int32 CurrentPosition;
};
