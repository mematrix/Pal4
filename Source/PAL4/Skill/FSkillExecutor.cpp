// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FSkillExecutor.h"

using namespace std;
using ResultPair = pair<reference_wrapper<ICharacterCombatDelegate>, FSkillResult>;


class PAL4_API FSkillActionCallback : public ISkillActionCallback
{
public:
    explicit FSkillActionCallback(ISkill& skill) : Skill(skill)
    {
    }

    void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FBasicInfoResult&) override
    {
    }

    void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FStatusInfoResult&) override
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
