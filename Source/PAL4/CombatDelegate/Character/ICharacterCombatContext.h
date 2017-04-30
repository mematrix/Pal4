#pragma once

class ICharacterRoundManager;
class ICharacterTempStatus;
class IPassiveActionInterceptor;


class PAL4_API ICharacterCombatContext
{
public:
    virtual ~ICharacterCombatContext()
    {
    }

    virtual ICharacterRoundManager& GetRoundManager() = 0;

    virtual ICharacterTempStatus& GetTempStatus() = 0;

    virtual IPassiveActionInterceptor& GetActionInterceptor() = 0;
};
