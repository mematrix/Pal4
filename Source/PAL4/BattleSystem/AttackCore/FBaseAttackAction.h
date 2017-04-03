#pragma once

#include "Delegate.h"

class ICharacterBattleStatus;

/*
 * 攻击动作的基类。封装了每种攻击（普攻、仙术攻击、技能攻击、物品攻击等）的基本流程
 */
class PAL4_API FBaseAttackAction
{
public:
    DECLARE_EVENT_TwoParams(FBaseAttackAction, FBeforeAttackEvent, const FBaseAttackAction&, const ICharacterBattleStatus&)
    DECLARE_EVENT_TwoParams(FBaseAttackAction, FOnAttackEvent, const FBaseAttackAction&, const ICharacterBattleStatus&)
    DECLARE_EVENT_TwoParams(FBaseAttackAction, FAfterAttackEvent, const FBaseAttackAction&, const ICharacterBattleStatus&)

public:
    FBaseAttackAction();
    FBaseAttackAction(const FBaseAttackAction&) = default;
    FBaseAttackAction& operator=(const FBaseAttackAction&) = default;

    virtual ~FBaseAttackAction() = default;

    FBeforeAttackEvent& BeforeAttack() { return BeforeAttackEvent; }
    FOnAttackEvent& OnAttack() { return OnAttackEvent; }
    FAfterAttackEvent& AfterAttack() { return AfterAttackEvent; }

protected:
    virtual void BeforeDoAttack(const ICharacterBattleStatus&);
    virtual void DoAttack();
    virtual void AfterDoAttack();

protected:
    const ICharacterBattleStatus* Character;

private:
    FBeforeAttackEvent BeforeAttackEvent;
    FOnAttackEvent OnAttackEvent;
    FAfterAttackEvent AfterAttackEvent;
};
