// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FSkillUtil.h"
#include "Combat/Interface/Character/ICharacterDelegate.h"
#include "Combat/Interface/Character/ICombatContext.h"
#include "Combat/Interface/Character/IStatusManager.h"
#include "Combat/Interface/Character/ISkillReactor.h"
#include "Character/Util/FCharacterHelper.h"
#include "Enum/ESkillAttribute.h"
#include "Model/FSkillInfo.h"
#include "Model/FSkillTriggerInfo.h"

using namespace std;
using ResultPair = pair<reference_wrapper<ICharacterDelegate>, FSkillResult>;


class PAL4_API FSkillActionCallback : public ISkillActionCallback
{
public:
    explicit FSkillActionCallback(ISkill& skill) : Skill(skill)
    {
    }

    void ApplyBasicInfoResult(const FBasicInfoResultRecord& record) override
    {
        auto& prop = record.Target->GetProperty();
        auto& result = *record.Result;
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

        if (FSkillUtil::CheckCategory(Skill, ESkillCategory::Attack))
        {
            record.Target->GetContext()->GetSkillReactor().OnBasicSkillFinished(record);
        }
    }

    void ApplyStatusInfoResult(const FStatusInfoResultRecord& record) override
    {
        auto context = record.Target->GetContext();
        auto& manager = context->GetStatusManager();
        auto& result = *record.Result;
        manager.SetStatusTransform(Skill.GetInfo().ID, result.StatusType, result.ValidRoundNum, result.TransformAction);

        if (FSkillUtil::CheckCategory(Skill, ESkillCategory::Attack))
        {
            context->GetSkillReactor().OnStatusSkillFinished(record);
        }
    }

    void ApplyTriggerResult(const FTriggerResultRecord& record) override
    {
        record.Target->GetContext()->GetSkillReactor().OnTriggerSkillFinished(record);
    }

    void ApplyCombatStatusResult(const FCombatStatusResultRecord& record) override
    {
        auto context = record.Target->GetContext();
        auto& manager = context->GetStatusManager();
        auto& result = *record.Result;
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

        if (FSkillUtil::CheckCategory(Skill, ESkillCategory::Attack))
        {
            context->GetSkillReactor().OnCombatStatusSkillFinished(record);
        }
    }

private:
    ISkill& Skill;
};


void FSkillUtil::Execute(ISkill& skill)
{
    list<ResultPair> resultList;
    skill.ComputeResult(resultList);
    // 通知被攻击对象修正技能结果（免疫等）
    for (auto& result : resultList)
    {
        result.first.get().GetContext()->GetSkillReactor().AmendResult(result.second);
    }

    skill.BeforeAction();

    FSkillActionCallback callback(skill);
    skill.DoAction(resultList, callback);

    auto attachSkill = skill.AttachedSkill();
    if (attachSkill.IsValid())
    {
        Execute(*attachSkill);
    }

    auto attr = skill.GetAttribute();
    auto category = GetSkillCategory(attr);
    if (ESkillCategory::Attack == category)
    {
        auto actor = skill.GetActor();

        FSkillTriggerInfo info;
        info.Source = GetSkillSource(attr);
        info.Actor = actor;
        for (auto& result : resultList)
        {
            if (result.second.HitTarget)
            {
                info.Target = &result.first.get();
                if (actor)
                {
                    actor->GetContext()->GetSkillReactor().TriggerSkill(info);
                }

                info.Target->GetContext()->GetSkillReactor().TriggerSkill(info);
            }
        }

        // TODO: 处理技能触发情况。如连击。怪物反击处理等到AfterAction结束后
    }

    skill.AfterAction();
}
