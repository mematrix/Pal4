#pragma once

#include <functional>

#include <SharedPointer.h>

#include "Combat/Interface/Round/IRoundAction.h"

class ICharacterDelegate;


class PAL4_API FNormalAttackAction : public IRoundAction
{
public:
    typedef TSharedRef<TArray<std::reference_wrapper<ICharacterDelegate>>> FTargetArray;

    FNormalAttackAction(ICharacterDelegate& actor, const FTargetArray& targets, int32 count, int32 craftGrowth);

    void BeforeDoAction() override final;

    void DoAction() override final;

    void AfterDoAction() override final;

protected:
    virtual ICharacterDelegate* PrepareHelp() { return nullptr; }

    virtual void FinishHelp() { }

    virtual void PrepareAttack() = 0;

    virtual void FinishAttack() = 0;

    /**
     * 一次攻击结束后的回调。如果人物单次动作包含多个攻击，每个攻击结束都会回调，此时countInAction代表了单次动作中的攻击计数
     * @param countOfAction 动作累积计数。即连击次数
     * @param countInAction 单次动作中攻击计数。注意不是总攻击次数
     * @param target 攻击目标
     */
    virtual void OnOneAttackFinished(int32 countOfAction, int32 countInAction, ICharacterDelegate& target) = 0;

    /**
     * 是否应该继续攻击（连击）
     */
    virtual bool CanAttackAgain() { return false; }

private:
    ICharacterDelegate& Actor;
    FTargetArray Targets;

    // 普通攻击分段次数（比如韩菱纱一次普通攻击会发出两次攻击）
    int32 Count;
    // 每次攻击气增量
    int32 CraftGrowthValue;
    // 援助者。nullptr表示无援助者
    ICharacterDelegate* Helper;
};
