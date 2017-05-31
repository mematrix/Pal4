#pragma once

#include "Skill/Enum/ESkillTriggerType.h"

class ICharacterDelegate;
class IRoundManager;
class IPassiveActionInterceptor;
class IStatusManager;
struct FBasicInfoResult;
struct FStatusInfoResult;
struct FTriggerResult;
struct FCombatStatusResult;


/**
 * ��ɫ����ս������ʱ�������������Ϣ
 */
class PAL4_API ICombatContext
{
public:
    virtual ~ICombatContext()
    {
    }

    virtual ICharacterDelegate& GetCharacter() = 0;

    virtual IRoundManager& GetRoundManager() = 0;

    virtual IPassiveActionInterceptor& GetActionInterceptor() = 0;

    virtual IStatusManager& GetStatusManager() = 0;

    /**
     * �ֶι����ļ���ÿ�ι����������ʱ����
     */
    virtual void OnBasicSkillFinished(ICharacterDelegate*, const FBasicInfoResult&) = 0;

    virtual void OnStatusSkillFinished(ICharacterDelegate*, const FStatusInfoResult&) = 0;

    virtual void OnTriggerSkillFinished(ICharacterDelegate*, const FTriggerResult&) = 0;

    virtual void OnCombatStatusSkillFinished(ICharacterDelegate*, const FCombatStatusResult&) = 0;

    /**
     * ����ָ������µļ��ܡ�
     * ���ڵ�ǰ������˵���ڶ�������Ϊ���ܹ����ߣ����ڼ����ͷ�����˵���ڶ�������Ϊ��ǰ����Ч��Ŀ��
     */
    virtual void TriggerSkillWithPeer(ESkillTriggerType, ICharacterDelegate&) = 0;

    virtual void TriggerSkill(ESkillTriggerType) = 0;
};
