#pragma once

#include <SharedPointer.h>
#include <Delegate.h>

#include "BattleSystem/RoundAction/IRoundActionHandler.h"

class FBaseAttackAction;
class ICharacterBattleDelegate;


class PAL4_API FRoundActionBaseHandler : IRoundActionHandler
{
public:
    DECLARE_EVENT_TwoParams(FRoundActionBaseHandler, FBeforeAttackEvent, const FRoundActionBaseHandler&, const FBaseAttackAction&)
    DECLARE_EVENT_TwoParams(FRoundActionBaseHandler, FOnAttackEvent, const FRoundActionBaseHandler&, const FBaseAttackAction&)
    DECLARE_EVENT_TwoParams(FRoundActionBaseHandler, FAfterAttackEvent, const FRoundActionBaseHandler&, const FBaseAttackAction&)

private:
    FBeforeAttackEvent BeforeAttackEvent;
    FOnAttackEvent OnAttackEvent;
    FAfterAttackEvent AfterAttackEvent;

public:
    explicit FRoundActionBaseHandler(const TSharedRef<ICharacterBattleDelegate>&);

    FBeforeAttackEvent& BeforeAttack() { return BeforeAttackEvent; }
    FOnAttackEvent& OnAttack() { return OnAttackEvent; }
    FAfterAttackEvent& AfterAttack() { return AfterAttackEvent; }

    void OnAction() override final;

protected:
    virtual TSharedRef<FBaseAttackAction> GetAttackAction() = 0;

private:
    TSharedRef<ICharacterBattleDelegate> Character;
};
