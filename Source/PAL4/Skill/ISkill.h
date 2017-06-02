#pragma once

#include <functional>
#include <list>

#include "Model/FSkillResultRecord.h"

class ICharacterDelegate;
struct FSkillInfo;


class PAL4_API ISkillActionCallback
{
public:
    virtual ~ISkillActionCallback() = default;

    virtual void ApplyBasicInfoResult(const FBasicInfoResultRecord&) = 0;

    virtual void ApplyStatusInfoResult(const FStatusInfoResultRecord&) = 0;

    virtual void ApplyTriggerResult(const FTriggerResultRecord&) = 0;

    virtual void ApplyCombatStatusResult(const FCombatStatusResultRecord&) = 0;
};


/**
 * 技能基类。定义了一个技能执行的基本过程
 */
class PAL4_API ISkill
{
public:
    typedef std::pair<std::reference_wrapper<ICharacterDelegate>, FSkillResult> ResultPair;

    virtual ~ISkill() = default;

    /**
     * 获取技能基本信息
     */
    virtual const FSkillInfo& GetInfo() const = 0;

    /**
     * 获取技能特性。五灵属性、攻击辅助等
     */
    virtual uint32 GetAttribute() const = 0;

    /**
     * 获取攻击者。无伤害来源的技能返回nullptr
     */
    virtual ICharacterDelegate* GetActor() = 0;

    /**
     * 计算技能执行预期结果。此结果将会继续由后续管道过程修正
     */
    virtual void ComputeResult(std::list<ResultPair>&) = 0;

    /**
     * 执行前奏动作
     */
    virtual void BeforeAction() = 0;

    /**
     * 执行技能过程。传入一个回调对象，用于完成技能结果结算
     */
    virtual void DoAction(const std::list<ResultPair>&, ISkillActionCallback&) = 0;

    /**
     * 执行后置动作
     */
    virtual void AfterAction() = 0;

    /**
     * 附加的技能，将会在当前技能@code ISkill::DoAction \endcode 调用结束、
     * @code ISkill::AfterAction \endcode 执行之前触发。
     * @return 附加技能。返回nullptr表示无附加技能
     */
    virtual TSharedPtr<ISkill> AttachedSkill() = 0;
};
