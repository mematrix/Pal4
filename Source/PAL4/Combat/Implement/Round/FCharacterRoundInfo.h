#pragma once

#include "Combat/Interface/Character/ICharacterDelegate.h"
#include "Combat/Interface/Character/ICombatContext.h"
#include "Combat/Interface/Character/IStatusManager.h"
#include "Combat/Interface/Character/ITemporaryStatus.h"
#include "Primitives/Model/FCharacterStatusInfo.h"
#include "Primitives/Model/FCharacterInherentInfo.h"
#include "Character/Util/FCharacterHelper.h"


class PAL4_API FCharacterRoundInfo
{
public:
    FCharacterRoundInfo(ICharacterDelegate& character, int32 position) :
        Character(character),
        CurrentPosition(position)
    {
    }

    int32 GetCurrentPosition() const { return CurrentPosition; }
    void SetCurrentPosition(int32 value) { CurrentPosition = value; }
    void AddCurrentPosition(int32 value) { CurrentPosition += value; }

    ICharacterDelegate& GetCharacter() { return Character; }
    const ICharacterDelegate& GetCharacter() const { return Character; }

    uint32 GetSpeedValue() const
    {
        return static_cast<uint32>(Character.GetContext()->GetStatusManager().GetTempStatus().GetAccumulatedInfo().SpeedPoint);
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
    ICharacterDelegate& Character;
    int32 CurrentPosition;
};
