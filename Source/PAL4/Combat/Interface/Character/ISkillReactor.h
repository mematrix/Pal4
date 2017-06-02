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
     * �������ܼ�����
     */
    virtual void AmendResult(FSkillResult&) = 0;

    /**
     * �ֶι����ļ���ÿ�ι����������ʱ����
     */
    virtual void OnBasicSkillFinished(const FBasicInfoResultRecord&) = 0;

    /**
     * �ֶι����ļ���ÿ�ι����������ʱ����
     */
    virtual void OnStatusSkillFinished(const FStatusInfoResultRecord&) = 0;

    /**
     * �ֶι����ļ���ÿ�ι����������ʱ����
     */
    virtual void OnTriggerSkillFinished(const FTriggerResultRecord&) = 0;

    /**
     * �ֶι����ļ���ÿ�ι����������ʱ����
     */
    virtual void OnCombatStatusSkillFinished(const FCombatStatusResultRecord&) = 0;

    /**
     * ����ָ������µļ���
     */
    virtual void TriggerSkill(const FSkillTriggerInfo&) = 0;
};

