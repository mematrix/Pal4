#pragma once

#include <SharedPointer.h>

struct FBaseAttackModel;
struct FBaseRestorerModel;
struct FBaseStatusModel;
class ICharacterBattleDelegate;


/**
 * ���ζ����Ļ��ࡣ��װ�˵��ζ������˺��͡��ָ��͡������ͣ��Ļ�������
 */
class PAL4_API ISingleAction
{
public:
    ISingleAction(ICharacterBattleDelegate& actor, ICharacterBattleDelegate& target) :
        Actor(actor),
        Target(target)
    {
    }

    ISingleAction(const ISingleAction&) = default;
    ISingleAction& operator=(const ISingleAction&) = default;

    virtual ~ISingleAction() = default;

    ICharacterBattleDelegate& GetActor() const { return Actor; }

    virtual void DoAction() = 0;

    // �����˺�ֵ������������״̬��ֻ���ǵ�ǰ���ԡ�������Ծ��ķ���Ч����
    virtual TSharedRef<FBaseAttackModel> ComputeAttackResult(const ICharacterBattleDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseRestorerModel> ComputeRestorerResult(const ICharacterBattleDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseStatusModel> ComputeStatusResult(const ICharacterBattleDelegate&, int32) const = 0;

    // �Զ���Ļص���������int32���͵�typeֵ�йأ���typeֵû�ж�ӦĬ�ϴ�����ʱ����������Զ��巽��
    virtual void CustomApplyAttackResult(ICharacterBattleDelegate&, const FBaseAttackModel&, int32) const { }
    virtual void CustomApplyRestorerResult(ICharacterBattleDelegate&, const FBaseRestorerModel&, int32) const { }
    virtual void CustomApplyStatusResult(ICharacterBattleDelegate&, const FBaseStatusModel&, int32) const { }

    // ֪ͨһ�ζ����Ѿ�����
    void OnAttackFinished(const ICharacterBattleDelegate&, const FBaseAttackModel&, int32) const;
    void OnRestorerFinished(const ICharacterBattleDelegate&, const FBaseRestorerModel&, int32) const;
    void OnStatusFinished(const ICharacterBattleDelegate&, const FBaseStatusModel&, int32) const;

protected:
    virtual void OnAttackFinishedOverride(const ICharacterBattleDelegate&, const FBaseAttackModel&, int32) const { }
    virtual void OnRestorerFinishedOverride(const ICharacterBattleDelegate&, const FBaseRestorerModel&, int32) const { }
    virtual void OnStatusFinishedOverride(const ICharacterBattleDelegate&, const FBaseStatusModel&, int32) const { }

    ICharacterBattleDelegate& Actor;
    ICharacterBattleDelegate& Target;
};
