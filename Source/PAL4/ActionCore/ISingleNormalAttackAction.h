#pragma once

#include "ISingleAction.h"


class PAL4_API ISingleNormalAttackAction final : public ISingleAction
{
public:
    ISingleNormalAttackAction(ICharacterBattleDelegate& actor, ICharacterBattleDelegate& target, int32 craftGrowth) :
        ISingleAction(actor, target),
        CraftGrowthValue(craftGrowth)
    {
    }

    void DoAction() override final;

protected:
    virtual void DoCompleteAttack() = 0;

    virtual void UpdateUI(const ICharacterBattleDelegate&, const FBaseAttackModel&, int32) = 0;

    /**
     * 是否应该继续攻击（连击）
     */
    virtual bool CanAttackAgain() { return false; }

    void DoOneAttack(ICharacterBattleDelegate&) const;

public:
    TSharedRef<FBaseRestorerModel> ComputeRestorerResult(const ICharacterBattleDelegate&, int32) const override;

    TSharedRef<FBaseStatusModel> ComputeStatusResult(const ICharacterBattleDelegate&, int32) const override;

protected:
    void OnAttackFinishedOverride(const ICharacterBattleDelegate&, const FBaseAttackModel&, int32) const override;

private:
    // 每次攻击气增量
    int32 CraftGrowthValue;
};
