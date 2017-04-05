#pragma once

#include "IRoundActionHandler.h"

class FCharacterPropertyManager;
class FCharacterProperty;

/*
 * ����ս��������ࡣ��Ϊһ��������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
 * ͬʱ�ṩս����������Ҫ����Ϣ�ͻص����ƽӿ�
 */
class PAL4_API ICharacterBattleStatus : public IRoundActionHandler
{
public:
    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual FCharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterProperty& GetCharacter() = 0;

    virtual void OnNormalAttackFinished(/*��ͨ�������Model*/) = 0;
    
    virtual void BeAttackedInNormal(/**/) = 0;

    virtual void OnMagicAttackFinished(/*�����������Model*/) = 0;

    virtual void BeAttackedWithMagic() = 0;

    virtual void OnSkillAttackFinished() = 0;

    virtual void BeAttackedWithSkill() = 0;

    virtual void OnPropAttackFinished() = 0;

    virtual void BeAttackedWithProp() = 0;
};
