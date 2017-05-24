#pragma once

#include <functional>
#include <list>

#include "FSkillResult.h"

class ICharacterCombatDelegate;


class PAL4_API ISkillActionCallback
{
public:
    virtual ~ISkillActionCallback() = default;

    virtual void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FBasicInfoResult&) = 0;

    virtual void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FStatusInfoResult&) = 0;

    virtual void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FTriggerResult&) = 0;

    virtual void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FCombatStatusResult&) = 0;
};


/**
 * 技能基类。定义了一个技能执行的基本过程
 */
class PAL4_API ISkill
{
public:
    typedef std::pair<std::reference_wrapper<ICharacterCombatDelegate>, FSkillResult> ResultPair;

    virtual ~ISkill() = default;

    virtual int32 GetID() const = 0;

    // TODO: using enum as ret value
    virtual int32 GetType() const = 0;

    /**
     * 计算技能执行预期结果。此结果将会继续由后续管道过程修正
     */
    virtual void ComputeResult(std::list<ResultPair>&) = 0;

    virtual void BeforeAction() = 0;

    /**
     * 执行技能过程。传入一个回调对象，用于完成技能结果结算
     */
    virtual void DoAction(const std::list<ResultPair>&, ISkillActionCallback&) = 0;

    virtual void AfterAction() = 0;

    /**
     * 附加的技能，将会在当前技能@code ISkill::DoAction \endcode 调用结束、
     * @code ISkill::AfterAction \endcode 执行之前触发。
     * 返回nullptr表示无附加技能
     */
    virtual TSharedPtr<ISkill> AttachedSkill() = 0;
};
