#pragma once

#include <SharedPointer.h>
#include <Array.h>

struct FBaseAttackModel;
struct FBaseRestorerModel;
struct FBaseStatusModel;
class ICharacterBattleDelegate;

/**
 * ���������Ļ��ࡣ��װ��ÿ�ֹ������չ����������������ܹ�������Ʒ�����ȣ��Ļ�������
 */
class PAL4_API ISingleAction
{
public:
    ISingleAction(const TSharedRef<ICharacterBattleDelegate>& attacker,
        const TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>>& charactersBeAttacked) :
        Attacker(attacker),
        CharactersBeAttacked(charactersBeAttacked)
    {
    }

    ISingleAction(const ISingleAction&) = default;
    ISingleAction& operator=(const ISingleAction&) = default;

    virtual ~ISingleAction() = default;

    virtual void BeforeDoAttack() { }
    virtual void DoAttack() = 0;
    virtual void AfterDoAttack() { }

    // �����˺�ֵ������������״̬��ֻ���ǵ�ǰ���ԡ�������Ծ��ķ���Ч����
    virtual TSharedRef<FBaseAttackModel> ComputeAttackResult(ICharacterBattleDelegate&, int32) = 0;
    virtual TSharedRef<FBaseRestorerModel> ComputeRestorerResult(ICharacterBattleDelegate&, int32) = 0;
    virtual TSharedRef<FBaseStatusModel> ComputeStatusResutl(ICharacterBattleDelegate&, int32) = 0;

protected:
    TSharedRef<ICharacterBattleDelegate> Attacker;
    TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>> CharactersBeAttacked;
};
