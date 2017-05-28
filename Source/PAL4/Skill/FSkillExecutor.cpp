// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FSkillExecutor.h"
#include "Combat/Interface/Character/ICharacterCombatDelegate.h"
#include "Combat/Interface/Character/ICharacterCombatContext.h"
#include "Combat/Interface/Character/IStatusManager.h"
#include "Character/Util/FCharacterHelper.h"

using namespace std;
using ResultPair = pair<reference_wrapper<ICharacterCombatDelegate>, FSkillResult>;


class PAL4_API FSkillActionCallback : public ISkillActionCallback
{
public:
    explicit FSkillActionCallback(ISkill& skill) : Skill(skill)
    {
    }

    void ApplyBasicInfoResult(ICharacterCombatDelegate* actor, ICharacterCombatDelegate& target, const FBasicInfoResult& result) override
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
            target.GetContext()->OnBasicSkillFinished(actor, result);
        }
    }

    void ApplyStatusInfoResult(ICharacterCombatDelegate* actor, ICharacterCombatDelegate& target, const FStatusInfoResult& result) override
    {
        auto& manager = target.GetContext()->GetStatusManager();
        manager.SetStatusTransform(Skill.GetID(), result.StatusType, result.ValidRoundNum, result.TransformAction);

        if (Skill.CanTriggerPassiveSkill())
        {
            target.GetContext()->OnStatusSkillFinished(actor, result);
        }
    }

    void ApplyTriggerResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FTriggerResult&) override
    {
    }

    void ApplyCombatStatusResult(ICharacterCombatDelegate* actor, ICharacterCombatDelegate& target, const FCombatStatusResult& result) override
    {
        auto& manager = target.GetContext()->GetStatusManager();
        switch (result.StatusType)
        {
        case ECombatStatus::Buff:
            manager.SetBuff(result.Status.Buff, result.MaxEffectRoundNum);
            break;

        case ECombatStatus::Invisible:
            manager.SetInvisible(result.Status.Invisible, result.MaxEffectRoundNum);
            break;

        case ECombatStatus::Resurrection:
            manager.SetResurrect(result.Status.CanResurrect, result.MaxEffectRoundNum);
            break;
        case ECombatStatus::Poison:
            manager.SetPoison(result.Status.Poison, result.MaxEffectRoundNum);
            break;

        case ECombatStatus::Debuff:
            manager.SetDebuff(result.Status.Debuff, result.MaxEffectRoundNum);
            break;

        default: break;
        }

        if (Skill.CanTriggerPassiveSkill())
        {
            target.GetContext()->OnCombatStatusSkillFinished(actor, result);
        }
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
