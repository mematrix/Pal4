// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FSkillExecutor.h"
#include "Combat/Interface/Character/ICharacterDelegate.h"
#include "Combat/Interface/Character/ICombatContext.h"
#include "Combat/Interface/Character/IStatusManager.h"
#include "Character/Util/FCharacterHelper.h"

using namespace std;
using ResultPair = pair<reference_wrapper<ICharacterDelegate>, FSkillResult>;


class PAL4_API FSkillActionCallback : public ISkillActionCallback
{
public:
    explicit FSkillActionCallback(ISkill& skill) : Skill(skill)
    {
    }

    void ApplyBasicInfoResult(ICharacterDelegate* actor, ICharacterDelegate& target, const FBasicInfoResult& result) override
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

    void ApplyStatusInfoResult(ICharacterDelegate* actor, ICharacterDelegate& target, const FStatusInfoResult& result) override
    {
        auto& manager = target.GetContext()->GetStatusManager();
        manager.SetStatusTransform(Skill.GetID(), result.StatusType, result.ValidRoundNum, result.TransformAction);

        if (Skill.CanTriggerPassiveSkill())
        {
            target.GetContext()->OnStatusSkillFinished(actor, result);
        }
    }

    void ApplyTriggerResult(ICharacterDelegate*, ICharacterDelegate&, const FTriggerResult&) override
    {
    }

    void ApplyCombatStatusResult(ICharacterDelegate* actor, ICharacterDelegate& target, const FCombatStatusResult& result) override
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

        case ECombatStatus::Resurrect:
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

    if (skill.CanTriggerPassiveSkill())
    {
        auto actor = skill.GetActor();
        if (actor)
        {
            actor->GetContext()->TriggerSkill(ESkillTriggerType::HitTarget);
        }

        // TODO: 处理技能触发情况。如连击。怪物反击处理等到AfterAction结束后
        for (auto& result : resultList)
        {
            result.first.get().GetContext()->TriggerSkill(ESkillTriggerType::HitByMagic);
        }
    }

    skill.AfterAction();
}
