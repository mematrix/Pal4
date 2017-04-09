#pragma once

#include <SharedPointer.h>
#include <Array.h>

class ICharacterBattleDelegate;

/**
 * ���������Ļ��ࡣ��װ��ÿ�ֹ������չ����������������ܹ�������Ʒ�����ȣ��Ļ�������
 */
class PAL4_API IAttackAction
{
public:
    IAttackAction(const TSharedRef<ICharacterBattleDelegate>& attacker,
        const TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>>& charactersBeAttacked) :
        Attacker(attacker),
        CharactersBeAttacked(charactersBeAttacked)
    {
    }

    IAttackAction(const IAttackAction&) = default;
    IAttackAction& operator=(const IAttackAction&) = default;

    virtual ~IAttackAction() = default;

    virtual void BeforeDoAttack() { }
    virtual void DoAttack() = 0;
    virtual void AfterDoAttack() { }

protected:
    TSharedRef<ICharacterBattleDelegate> Attacker;
    TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>> CharactersBeAttacked;
};
