#pragma once

#include "BattleDelegate/Character/ICharacterBattleDelegate.h"
#include "BattleDelegate/Character/ICharacterBattleContext.h"
#include "BattleDelegate/Character/ICharacterTempStatusAccessor.h"
#include "BattleDelegate/Character/ICharacterPropertyManager.h"
#include "CharacterPrimitives/Model/FCharacterStatusInfo.h"


class PAL4_API FCharacterRoundInfo
{
public:
    FCharacterRoundInfo(ICharacterBattleDelegate& character, int32 position) :
        Character(character),
        CurrentPosition(position)
    {
    }

    int32 GetCurrentPosition() const { return CurrentPosition; }
    void SetCurrentPosition(int32 value) { CurrentPosition = value; }
    void AddCurrentPosition(int32 value) { CurrentPosition += value; }

    ICharacterBattleDelegate& GetCharacter() { return Character; }
    const ICharacterBattleDelegate& GetCharacter() const { return Character; }

    uint32 GetSpeedValue() const
    {
        return static_cast<uint32>(Character.GetContext()->GetTempStatusAccessor().GetAccumulatedInfo().SpeedPoint);
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
    ICharacterBattleDelegate& Character;
    int32 CurrentPosition;
};
