#pragma once

class ISupportRoundAction;
class FCharacterPropertyManager;
class FCharacterBasicInfo;

class PAL4_API ICharacterBattleStatus
{
public:
    virtual ~ICharacterBattleStatus()
    {
    }

    virtual ISupportRoundAction& GetRoundAction() = 0;

    virtual FCharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterBasicInfo& GetCharacter() = 0;
};
