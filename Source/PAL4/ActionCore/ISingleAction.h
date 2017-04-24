#pragma once

#include <SharedPointer.h>

struct FBaseAttackModel;
struct FBaseRestorerModel;
struct FBaseStatusModel;
class ICharacterCombatDelegate;


/**
 * ���ζ����Ļ��ࡣ��װ�˵��ζ������˺��͡��ָ��͡������ͣ��Ļ�������
 */
class PAL4_API ISingleAction
{
public:
    ISingleAction(ICharacterCombatDelegate& actor, ICharacterCombatDelegate& target) :
        Actor(actor),
        Target(target)
    {
    }

    ISingleAction(const ISingleAction&) = default;
    ISingleAction& operator=(const ISingleAction&) = default;

    virtual ~ISingleAction() = default;

    ICharacterCombatDelegate& GetActor() const { return Actor; }

    virtual void DoAction() = 0;

    // �����˺�ֵ������������״̬��ֻ���ǵ�ǰ���ԡ�������Ծ��ķ���Ч����
    virtual TSharedRef<FBaseAttackModel> ComputeAttackResult(const ICharacterCombatDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseRestorerModel> ComputeRestorerResult(const ICharacterCombatDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseStatusModel> ComputeStatusResult(const ICharacterCombatDelegate&, int32) const = 0;

    // �Զ���Ļص���������int32���͵�typeֵ�йأ���typeֵû�ж�ӦĬ�ϴ�����ʱ����������Զ��巽��
    virtual void CustomApplyAttackResult(ICharacterCombatDelegate&, const FBaseAttackModel&, int32) const { }
    virtual void CustomApplyRestorerResult(ICharacterCombatDelegate&, const FBaseRestorerModel&, int32) const { }
    virtual void CustomApplyStatusResult(ICharacterCombatDelegate&, const FBaseStatusModel&, int32) const { }

    // ֪ͨһ�ζ����Ѿ�����
    void OnAttackFinished(const ICharacterCombatDelegate&, const FBaseAttackModel&, int32) const;
    void OnRestorerFinished(const ICharacterCombatDelegate&, const FBaseRestorerModel&, int32) const;
    void OnStatusFinished(const ICharacterCombatDelegate&, const FBaseStatusModel&, int32) const;

protected:
    virtual void OnAttackFinishedOverride(const ICharacterCombatDelegate&, const FBaseAttackModel&, int32) const { }
    virtual void OnRestorerFinishedOverride(const ICharacterCombatDelegate&, const FBaseRestorerModel&, int32) const { }
    virtual void OnStatusFinishedOverride(const ICharacterCombatDelegate&, const FBaseStatusModel&, int32) const { }

    ICharacterCombatDelegate& Actor;
    ICharacterCombatDelegate& Target;
};
