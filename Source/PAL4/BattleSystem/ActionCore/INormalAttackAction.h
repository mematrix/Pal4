#pragma once

#include "ISingleAction.h"


class PAL4_API INormalAttackAction : public ISingleAction
{
public:
    INormalAttackAction(ICharacterBattleDelegate& actor, const FTargetArray& targets, int32 craftGrowth) :
        ISingleAction(actor, targets),
        CraftGrowthValue(craftGrowth)
    {
    }

    void BeforeDoAction() override final
    {
        PrepareHelp();
        PrepareAttack();
    }

    void DoAction() override final;

    void AfterDoAction() override final
    {
        FinishAttack();
        FinishHelp();
    }

protected:
    virtual void PrepareHelp() { }

    virtual void FinishHelp() { }

    virtual void PrepareAttack() = 0;

    virtual void FinishAttack() = 0;

    virtual void DoCompleteAttack() = 0;

    virtual void UpdateUI(const ICharacterBattleDelegate&, const FBaseAttackModel&, int32) = 0;

    /**
     * �Ƿ�Ӧ�ü���������������
     */
    virtual bool CanAttackAgain() { return false; }

    void DoOneAttack(ICharacterBattleDelegate&) const;

public:
    TSharedRef<FBaseRestorerModel> ComputeRestorerResult(const ICharacterBattleDelegate&, int32) const override;

    TSharedRef<FBaseStatusModel> ComputeStatusResult(const ICharacterBattleDelegate&, int32) const override;

protected:
    void OnAttackFinishedOverride(const ICharacterBattleDelegate&, const FBaseAttackModel&, int32) const override;

private:
    // ÿ�ι���������
    int32 CraftGrowthValue;
};
