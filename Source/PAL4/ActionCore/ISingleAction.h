#pragma once

#include <SharedPointer.h>

struct FBaseAttackModel;
struct FBaseRestorerModel;
struct FBaseStatusModel;
class ICharacterDelegate;


/**
 * 单次动作的基类。封装了单次动作（伤害型、恢复型、辅助型）的基本数据
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

    // 计算伤害值（不考虑人物状态，只考虑当前属性。例如忽略镜的反弹效果）
    virtual TSharedRef<FBaseAttackModel> ComputeAttackResult(const ICharacterDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseRestorerModel> ComputeRestorerResult(const ICharacterDelegate&, int32) const = 0;
    virtual TSharedRef<FBaseStatusModel> ComputeStatusResult(const ICharacterDelegate&, int32) const = 0;

    // 自定义的回调函数。与int32类型的type值有关，当type值没有对应默认处理函数时，将会调用自定义方法
    virtual void CustomApplyAttackResult(ICharacterDelegate&, const FBaseAttackModel&, int32) const { }
    virtual void CustomApplyRestorerResult(ICharacterDelegate&, const FBaseRestorerModel&, int32) const { }
    virtual void CustomApplyStatusResult(ICharacterDelegate&, const FBaseStatusModel&, int32) const { }

    // 通知一次动作已经结束
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
