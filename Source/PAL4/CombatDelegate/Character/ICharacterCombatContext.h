#pragma once

class ICharacterRoundManager;
class ICharacterTempStatusAccessor;
class IPassiveActionInterceptor;


class PAL4_API ICharacterCombatContext
{
public:
    virtual ~ICharacterCombatContext()
    {
    }

    virtual ICharacterRoundManager& GetRoundManager() = 0;

    virtual ICharacterTempStatusAccessor& GetTempStatusAccessor() = 0;

    virtual IPassiveActionInterceptor& GetActionInterceptor() = 0;
};
