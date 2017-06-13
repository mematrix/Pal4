#pragma once

struct FBasicInfoResultRecord;
struct FStatusInfoResultRecord;
struct FTriggerResultRecord;
struct FCombatStatusResultRecord;
struct FSkillTriggerInfo;
struct FSkillResult;

class ISkill;


class PAL4_API ISkillReactor
{
public:
    virtual ~ISkillReactor() = default;

    /**
     * 修正技能计算结果
     */
    virtual void AmendResult(FSkillResult&, const ISkill&) = 0;

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
     * 触发指定情况下的技能，第二个参数指示是攻击方还是被攻击者
     */
    virtual void TriggerSkill(const FSkillTriggerInfo&, bool) = 0;
};

