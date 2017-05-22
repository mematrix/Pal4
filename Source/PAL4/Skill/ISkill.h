#pragma once

#include <functional>
#include <map>

#include "FSkillResult.h"

class ICharacterCombatDelegate;


/**
 * 技能基类。定义了一个技能执行的基本过程
 */
class PAL4_API ISkill
{
public:
    virtual ~ISkill() = default;

    /**
     * 计算技能执行预期结果。此结果将会继续由后续管道过程修正
     */
    virtual void ComputeResult(std::map<std::reference_wrapper<ICharacterCombatDelegate>, FSkillResult>&) = 0;

    virtual void BeforeAction() = 0;

    /**
     * 执行技能过程。传入一个回调函数，此函数接受三个参数：攻击者、被攻击对象以及伤害模型对象
     */
    virtual void DoAction(const std::map<std::reference_wrapper<ICharacterCombatDelegate>, FSkillResult>&,
        const std::function<void(ICharacterCombatDelegate&, ICharacterCombatDelegate&, const FSkillResult&)>&) = 0;

    virtual void AfterAction() = 0;
};
