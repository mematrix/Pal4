#pragma once

struct FBasicInfoResultRecord;
struct FStatusInfoResultRecord;
struct FTriggerResultRecord;
struct FCombatStatusResultRecord;
struct FSkillTriggerInfo;
struct FSkillResult;


class PAL4_API ISkillReactor
{
public:
    virtual ~ISkillReactor() = default;

    /*
     * 修正技能计算结果
     */
    virtual void AmendResult(FSkillResult&) = 0;

    /**
     * 分段攻击的技能每段攻击结果结束时触发
     */
    virtual void OnBasicSkillFinished(const FBasicInfoResultRecord&) = 0;

    /**
     * 分段攻击的技能每段攻击结果结束时触发
     */
    virtual void OnStatusSkillFinished(const FStatusInfoResultRecord&) = 0;

    /**
     * 分段攻击的技能每段攻击结果结束时触发
     */
    virtual void OnTriggerSkillFinished(const FTriggerResultRecord&) = 0;

    /**
     * 分段攻击的技能每段攻击结果结束时触发
     */
    virtual void OnCombatStatusSkillFinished(const FCombatStatusResultRecord&) = 0;

    /**
     * 触发指定情况下的技能
     */
    virtual void TriggerSkill(const FSkillTriggerInfo&) = 0;
};

