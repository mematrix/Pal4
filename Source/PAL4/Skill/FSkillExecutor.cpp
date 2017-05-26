// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FSkillExecutor.h"
#include "Combat/Interface/Character/ICharacterCombatDelegate.h"
#include "Combat/Interface/Character/ICharacterCombatContext.h"
#include "Character/Util/FCharacterHelper.h"

using namespace std;
using ResultPair = pair<reference_wrapper<ICharacterCombatDelegate>, FSkillResult>;


class PAL4_API FSkillActionCallback : public ISkillActionCallback
{
public:
    explicit FSkillActionCallback(ISkill& skill) : Skill(skill)
    {
    }

    void ApplyResult(ICharacterCombatDelegate* actor, ICharacterCombatDelegate& target, const FBasicInfoResult& result) override
    {
        auto& prop = target.GetProperty();
        if (result.HealthValue)
        {
            FCharacterHelper::AddHealthValue(prop, result.HealthValue);
        }
        if (result.ManaValue)
        {
            FCharacterHelper::AddManaValue(prop, result.ManaValue);
        }
        if (result.CraftValue)
        {
            FCharacterHelper::AddCraftValue(prop, result.CraftValue);
        }

        if (Skill.CanTriggerPassiveSkill())
        {
            target.GetContext()->OnSkillSubstepFinished(actor, result);
        }
    }

    void ApplyResult(ICharacterCombatDelegate* actor, ICharacterCombatDelegate& target, const FStatusInfoResult& result) override
    {

    }

    void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FTriggerResult&) override
    {
    }

    void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FCombatStatusResult&) override
    {
    }

private:
    ISkill& Skill;
};


void FSkillExecutor::Execute(ISkill& skill)
{
    list<ResultPair> resultList;
    skill.ComputeResult(resultList);
    // TODO: 通知被攻击对象修正技能结果（免疫等）

    skill.BeforeAction();

    FSkillActionCallback callback(skill);
    skill.DoAction(resultList, callback);

    auto attachSkill = skill.AttachedSkill();
    if (attachSkill.IsValid())
    {
        Execute(*attachSkill);
    }

    skill.AfterAction();
}
