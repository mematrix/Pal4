#pragma once

#include "IRoundActionHandler.h"

class FCharacterPropertyManager;
class FCharacterProperty;

class PAL4_API ICharacterBattleStatus : public IRoundActionHandler
{
public:
    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual FCharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterProperty& GetCharacter() = 0;
};
