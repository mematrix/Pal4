#pragma once

#include <SharedPointer.h>

struct FBaseAttackModel;
struct FBaseRestorerModel;
struct FBaseStatusModel;
class ICharacterDelegate;


/**
 * ���ζ����Ļ��ࡣ��װ�˵��ζ������˺��͡��ָ��͡������ͣ��Ļ�������
 */
class PAL4_API ISingleAction
{
public:
    ISingleAction(ICharacterDelegate& actor, ICharacterDelegate& target) :
        Actor(actor),
        Target(target)
    {
    }

    ISingleAction(const ISingleAction&) = default;
    ISingleAction& operator=(const ISingleAction&) = default;

    virtual ~ISingleAction() = default;

    ICharacterDelegate& GetActor() const { return Actor; }

    virtual void DoAction() = 0;

    // �����˺�ֵ������������״̬��ֻ���ǵ�ǰ���ԡ�������Ծ��ķ���Ч����
    virtual TSharedRef<FBaseAttackModel> ComputeAttackResult(const ICharacterDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseRestorerModel> ComputeRestorerResult(const ICharacterDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseStatusModel> ComputeStatusResult(const ICharacterDelegate&, int32) const = 0;

    // �Զ���Ļص���������int32���͵�typeֵ�йأ���typeֵû�ж�ӦĬ�ϴ�����ʱ����������Զ��巽��
    virtual void CustomApplyAttackResult(ICharacterDelegate&, const FBaseAttackModel&, int32) const { }
    virtual void CustomApplyRestorerResult(ICharacterDelegate&, const FBaseRestorerModel&, int32) const { }
    virtual void CustomApplyStatusResult(ICharacterDelegate&, const FBaseStatusModel&, int32) const { }

    // ֪ͨһ�ζ����Ѿ�����
    void OnAttackFinished(const ICharacterDelegate&, const FBaseAttackModel&, int32) const;
    void OnRestorerFinished(const ICharacterDelegate&, const FBaseRestorerModel&, int32) const;
    void OnStatusFinished(const ICharacterDelegate&, const FBaseStatusModel&, int32) const;

protected:
    virtual void OnAttackFinishedOverride(const ICharacterDelegate&, const FBaseAttackModel&, int32) const { }
    virtual void OnRestorerFinishedOverride(const ICharacterDelegate&, const FBaseRestorerModel&, int32) const { }
    virtual void OnStatusFinishedOverride(const ICharacterDelegate&, const FBaseStatusModel&, int32) const { }

    ICharacterDelegate& Actor;
    ICharacterDelegate& Target;
};
