#pragma once

#include "Skill/Enum/ESkillTriggerType.h"

class ICharacterDelegate;
class IRoundManager;
class ISkillReactor;
class IStatusManager;

struct FBasicInfoResult;
struct FStatusInfoResult;
struct FTriggerResult;
struct FCombatStatusResult;
struct FSkillTriggerInfo;


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

    virtual ISkillReactor& GetActionInterceptor() = 0;

    virtual IStatusManager& GetStatusManager() = 0;

    /**
     * �ֶι����ļ���ÿ�ι����������ʱ����
     */
    virtual void OnBasicSkillFinished(ICharacterDelegate*, const FBasicInfoResult&) = 0;

    virtual void OnStatusSkillFinished(ICharacterDelegate*, const FStatusInfoResult&) = 0;

    virtual void OnTriggerSkillFinished(ICharacterDelegate*, const FTriggerResult&) = 0;

    virtual void OnCombatStatusSkillFinished(ICharacterDelegate*, const FCombatStatusResult&) = 0;

    /**
     * ����ָ������µļ���
     */
    virtual void TriggerSkill(const FSkillTriggerInfo&) = 0;
};
