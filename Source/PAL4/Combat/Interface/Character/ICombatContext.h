#pragma once

class ICharacterDelegate;
class IRoundManager;
class IPassiveActionInterceptor;
class IStatusManager;
struct FBasicInfoResult;
struct FStatusInfoResult;
struct FTriggerResult;
struct FCombatStatusResult;


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

    virtual IPassiveActionInterceptor& GetActionInterceptor() = 0;

    virtual IStatusManager& GetStatusManager() = 0;

    /**
     * 分段攻击的技能每段攻击结果结束时触发
     */
    virtual void OnBasicSkillFinished(ICharacterDelegate*, const FBasicInfoResult&) = 0;

    virtual void OnStatusSkillFinished(ICharacterDelegate*, const FStatusInfoResult&) = 0;

    virtual void OnTriggerSkillFinished(ICharacterDelegate*, const FTriggerResult&) = 0;

    virtual void OnCombatStatusSkillFinished(ICharacterDelegate*, const FCombatStatusResult&) = 0;
};
