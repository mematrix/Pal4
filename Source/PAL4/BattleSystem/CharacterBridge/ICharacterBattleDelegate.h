#pragma once

class IRoundActionHandler;
class ICharacterPropertyManager;
class FCharacterPersistentStatus;
class ICharacterRoundManager;

/*
 * ����ս��������ࡣ��Ϊһ��������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
 * ͬʱ�ṩս����������Ҫ����Ϣ�ͻص����ƽӿ�
 */
class PAL4_API ICharacterBattleDelegate
{
public:
    virtual ~ICharacterBattleDelegate()
    {
    }

    virtual ICharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterPersistentStatus& GetPersistentStatus() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnBattleBegin(const ICharacterRoundManager&) = 0;

    virtual void OnBattleFinished() = 0;

    virtual void OnNormalAttackFinished(/*��ͨ�������Model*/) = 0;
    
    virtual void BeAttackedInNormal(/**/) = 0;

    virtual void OnMagicAttackFinished(/*�����������Model*/) = 0;

    virtual void BeAttackedWithMagic() = 0;

    virtual void OnSkillAttackFinished() = 0;

    virtual void BeAttackedWithSkill() = 0;

    virtual void OnPropAttackFinished() = 0;

    virtual void BeAttackedWithProp() = 0;
};
