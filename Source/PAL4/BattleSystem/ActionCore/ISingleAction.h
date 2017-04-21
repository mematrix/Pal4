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
    ISingleAction(const TSharedRef<ICharacterBattleDelegate>& actor,
        const TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>>& targets) :
        Actor(actor),
        Targets(targets)
    {
    }

    ISingleAction(const ISingleAction&) = default;
    ISingleAction& operator=(const ISingleAction&) = default;

    virtual ~ISingleAction() = default;

    const TSharedRef<ICharacterBattleDelegate>& GetActor() const { return Actor; }

    virtual void BeforeDoAttack() { }
    virtual void DoAttack() = 0;
    virtual void AfterDoAttack() { }

    // �����˺�ֵ������������״̬��ֻ���ǵ�ǰ���ԡ�������Ծ��ķ���Ч����
    virtual TSharedRef<FBaseAttackModel> ComputeAttackResult(const ICharacterBattleDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseRestorerModel> ComputeRestorerResult(const ICharacterBattleDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseStatusModel> ComputeStatusResult(const ICharacterBattleDelegate&, int32) const = 0;

    // �Զ���Ļص���������int32���͵�typeֵ�йأ���typeֵû�ж�ӦĬ�ϴ�����ʱ����������Զ��巽��
    virtual void CustomApplyAttackResult(ICharacterBattleDelegate&, const FBaseAttackModel&, int32) const { }
    virtual void CustomApplyRestorerResult(ICharacterBattleDelegate&, const FBaseRestorerModel&, int32) const { }
    virtual void CustomApplyStatusResult(ICharacterBattleDelegate&, const FBaseStatusModel&, int32) const { }

protected:
    TSharedRef<ICharacterBattleDelegate> Actor;
    TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>> Targets;
};
