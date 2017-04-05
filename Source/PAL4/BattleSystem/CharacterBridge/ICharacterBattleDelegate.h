#pragma once

#include "IRoundActionHandler.h"

class FCharacterPropertyManager;
class FCharacterProperty;

/*
 * 人物战斗代理基类。作为一个代理，在战斗过程中，提供对人物属性的访问和设置接口；
 * 同时提供战斗过程中需要的信息和回调控制接口
 */
class PAL4_API ICharacterBattleStatus : public IRoundActionHandler
{
public:
    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual FCharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterProperty& GetCharacter() = 0;

    virtual void OnNormalAttackFinished(/*普通攻击结果Model*/) = 0;
    
    virtual void BeAttackedInNormal(/**/) = 0;

    virtual void OnMagicAttackFinished(/*仙术攻击结果Model*/) = 0;

    virtual void BeAttackedWithMagic() = 0;

    virtual void OnSkillAttackFinished() = 0;

    virtual void BeAttackedWithSkill() = 0;

    virtual void OnPropAttackFinished() = 0;

    virtual void BeAttackedWithProp() = 0;
};
