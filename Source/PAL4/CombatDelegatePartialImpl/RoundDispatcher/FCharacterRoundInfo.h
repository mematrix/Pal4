#pragma once

#include "CombatDelegate/Character/ICharacterCombatDelegate.h"
#include "CombatDelegate/Character/ICharacterCombatContext.h"
#include "CombatDelegate/Character/ICharacterTempStatus.h"
#include "CombatDelegate/Character/ICharacterPropertyManager.h"
#include "Primitives/Model/FCharacterStatusInfo.h"


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
        return Character.GetPropertyManager().IsAlive();
    }

    int32 GetCharacterId() const
    {
        return Character.GetPropertyManager().GetId();
    }

private:
    ICharacterCombatDelegate& Character;
    int32 CurrentPosition;
};
