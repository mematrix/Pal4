#pragma once

#include "ISingleAction.h"


class PAL4_API ISingleNormalAttackAction final : public ISingleAction
{
public:
    ISingleNormalAttackAction(ICharacterDelegate& actor, ICharacterDelegate& target, int32 craftGrowth) :
        ISingleAction(actor, target),
        CraftGrowthValue(craftGrowth)
    {
    }

    void DoAction() override final;

protected:
    virtual void DoCompleteAttack() = 0;

    virtual void UpdateUI(const ICharacterDelegate&, const FBaseAttackModel&, int32) = 0;

    /**
     * 是否应该继续攻击（连击）
     */
    virtual bool CanAttackAgain() { return false; }

    void DoOneAttack(ICharacterDelegate&) const;

public:
    TSharedRef<FBaseRestorerModel> ComputeRestorerResult(const ICharacterDelegate&, int32) const override;

    TSharedRef<FBaseStatusModel> ComputeStatusResult(const ICharacterDelegate&, int32) const override;

protected:
    void OnAttackFinishedOverride(const ICharacterDelegate&, const FBaseAttackModel&, int32) const override;

private:
    // 每次攻击气增量
    int32 CraftGrowthValue;
};
