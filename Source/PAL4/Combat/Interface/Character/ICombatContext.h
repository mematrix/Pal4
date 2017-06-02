#pragma once

class ICharacterDelegate;
class IRoundManager;
class ISkillReactor;
class IStatusManager;


/**
 * 角色处于战斗场景时的相关上下文信息
 */
class PAL4_API ICombatContext
{
public:
    virtual ~ICombatContext()
    {
    }

    virtual ICharacterDelegate& GetCharacter() = 0;

    virtual IRoundManager& GetRoundManager() = 0;

    virtual ISkillReactor& GetSkillReactor() = 0;

    virtual IStatusManager& GetStatusManager() = 0;
};
