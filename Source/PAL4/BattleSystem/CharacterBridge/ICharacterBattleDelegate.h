#pragma once

#include <functional>

class IRoundActionHandler;
class ICharacterPropertyManager;
class FCharacterPersistentStatus;
class ICharacterRoundManager;
class ICharacterTemporaryStatus;

/*
 * ����ս���������ࡣ��Ϊһ����������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
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

    virtual void OnBattleBegin(const ICharacterRoundManager&, const ICharacterTemporaryStatus&) = 0;

    virtual void OnBattleFinished() = 0;

    virtual void OnNormalAttackFinished(/*��ͨ�������Model*/) = 0;
    
    virtual void BeAttackedInNormal(/**/) = 0;

    virtual void OnMagicAttackFinished(/*�����������Model*/) = 0;

    virtual void BeAttackedWithMagic() = 0;

    virtual void OnSkillAttackFinished() = 0;

    virtual void BeAttackedWithSkill() = 0;

    virtual void OnPropAttackFinished() = 0;

    virtual void BeAttackedWithProp() = 0;

    /**
    * ���ý�ɫ����ʱ�Ļص���
    * @warning Ŀǰ������ @code ICharacterRoundDispatcher\endcode ��
    */
    virtual void SetOnDeadCallback(std::function<void(const ICharacterBattleDelegate&)>) = 0;
    /**
    * ���ý�ɫ����ʱ�Ļص���
    * @warning Ŀǰ������ @code ICharacterRoundDispatcher\endcode ��
    */
    virtual void SetOnReviveCallback(std::function<void(const ICharacterBattleDelegate&)>) = 0;
};