#pragma once

class ICharacterCombatDelegate;
class ICharacterRoundManager;
class ICharacterTempStatus;
class IPassiveActionInterceptor;
struct FBasicInfoResult;
struct FStatusInfoResult;
struct FTriggerResult;
struct FCombatStatusResult;


/**
 * 角色处于战斗场景时的相关上下文信息
 */
class PAL4_API ICharacterCombatContext
{
public:
    virtual ~ICharacterCombatContext()
    {
    }

    virtual ICharacterCombatDelegate& GetCharacter() = 0;

    virtual ICharacterRoundManager& GetRoundManager() = 0;

    virtual ICharacterTempStatus& GetTempStatus() = 0;

    virtual IPassiveActionInterceptor& GetActionInterceptor() = 0;

    virtual void OnSkillSubstepFinished(ICharacterCombatDelegate*, const FBasicInfoResult&) = 0;

    virtual void OnSkillSubstepFinished(ICharacterCombatDelegate*, const FStatusInfoResult&) = 0;

    virtual void OnSkillSubstepFinished(ICharacterCombatDelegate*, const FTriggerResult&) = 0;

    virtual void OnSkillSubstepFinished(ICharacterCombatDelegate*, const FCombatStatusResult&) = 0;
};
