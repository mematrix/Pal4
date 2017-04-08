#pragma once

#include "BattleSystem/Character/FBattleCharacter.h"
#include "BattleSystem/CharacterBridge/ICharacterPropertyManager.h"

class PAL4_API FCharacterRoundInfo
{
public:
    FCharacterRoundInfo(const FBattleCharacter& character, int32 position) : 
        Character(character),
        CurrentPosition(0)
    {
    }

    int32 GetCurrentPosition() const { return CurrentPosition; }
    void SetCurrentPosition(int32 value) { CurrentPosition = value; }
    void AddCurrentPosition(int32 value) { CurrentPosition += value; }
    const FBattleCharacter& GetCharacter() const { return Character; }

    uint32 GetSpeedValue() const
    {
        return static_cast<uint32>(Character.GetTemporaryStatus().GetAccumulatedInfo().SpeedPoint);
    }

    bool IsAlive() const
    {
        return Character.GetCharacterDelegate().GetPropertyManager().IsAlive();
    }

    int32 GetCharacterId() const
    {
        return Character.GetCharacterDelegate().GetPropertyManager().GetId();
    }

private:
    const FBattleCharacter& Character;
    int32 CurrentPosition;
};
