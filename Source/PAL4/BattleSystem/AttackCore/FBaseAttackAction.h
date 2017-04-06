#pragma once

#include "Delegate.h"

class ICharacterBattleDelegate;

/*
 * ���������Ļ��ࡣ��װ��ÿ�ֹ������չ����������������ܹ�������Ʒ�����ȣ��Ļ�������
 */
class PAL4_API FBaseAttackAction
{
public:
    DECLARE_EVENT_TwoParams(FBaseAttackAction, FBeforeAttackEvent, const FBaseAttackAction&, const ICharacterBattleDelegate&)
    DECLARE_EVENT_TwoParams(FBaseAttackAction, FOnAttackEvent, const FBaseAttackAction&, const ICharacterBattleDelegate&)
    DECLARE_EVENT_TwoParams(FBaseAttackAction, FAfterAttackEvent, const FBaseAttackAction&, const ICharacterBattleDelegate&)

public:
    FBaseAttackAction();
    FBaseAttackAction(const FBaseAttackAction&) = default;
    FBaseAttackAction& operator=(const FBaseAttackAction&) = default;

    virtual ~FBaseAttackAction() = default;

    FBeforeAttackEvent& BeforeAttack() { return BeforeAttackEvent; }
    FOnAttackEvent& OnAttack() { return OnAttackEvent; }
    FAfterAttackEvent& AfterAttack() { return AfterAttackEvent; }

protected:
    virtual void BeforeDoAttack(const ICharacterBattleDelegate&);
    virtual void DoAttack();
    virtual void AfterDoAttack();

protected:
    const ICharacterBattleDelegate* Character;

private:
    FBeforeAttackEvent BeforeAttackEvent;
    FOnAttackEvent OnAttackEvent;
    FAfterAttackEvent AfterAttackEvent;
};
