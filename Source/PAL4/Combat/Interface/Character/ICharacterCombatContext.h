#pragma once

class ICharacterCombatDelegate;
class IRoundManager;
class ITemporaryStatus;
class IPassiveActionInterceptor;
class IStatusManager;
struct FBasicInfoResult;
struct FStatusInfoResult;
struct FTriggerResult;
struct FCombatStatusResult;


/**
 * ��ɫ����ս������ʱ�������������Ϣ
 */
class PAL4_API ICharacterCombatContext
{
public:
    virtual ~ICharacterCombatContext()
    {
    }

    virtual ICharacterCombatDelegate& GetCharacter() = 0;

    virtual IRoundManager& GetRoundManager() = 0;

    virtual ITemporaryStatus& GetTempStatus() = 0;

    virtual IPassiveActionInterceptor& GetActionInterceptor() = 0;

    virtual IStatusManager& GetStatusManager() = 0;

    /**
     * �ֶι����ļ���ÿ�ι����������ʱ����
     */
    virtual void OnBasicSkillFinished(ICharacterCombatDelegate*, const FBasicInfoResult&) = 0;

    virtual void OnStatusSkillFinished(ICharacterCombatDelegate*, const FStatusInfoResult&) = 0;

    virtual void OnTriggerSkillFinished(ICharacterCombatDelegate*, const FTriggerResult&) = 0;

    virtual void OnCombatStatusSkillFinished(ICharacterCombatDelegate*, const FCombatStatusResult&) = 0;
};
