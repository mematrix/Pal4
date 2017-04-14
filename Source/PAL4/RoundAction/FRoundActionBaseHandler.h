#pragma once

#include <SharedPointer.h>
#include <Delegate.h>

#include "BattleSystem/RoundAction/IRoundActionHandler.h"

class ISingleAction;
class ICharacterBattleDelegate;


class PAL4_API FRoundActionBaseHandler : IRoundActionHandler
{
public:
    DECLARE_EVENT_TwoParams(FRoundActionBaseHandler, FBeforeAttackEvent, const FRoundActionBaseHandler&, const ISingleAction&)
    DECLARE_EVENT_TwoParams(FRoundActionBaseHandler, FOnAttackEvent, const FRoundActionBaseHandler&, const ISingleAction&)
    DECLARE_EVENT_TwoParams(FRoundActionBaseHandler, FAfterAttackEvent, const FRoundActionBaseHandler&, const ISingleAction&)

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
    virtual TSharedRef<ISingleAction> GetAttackAction() = 0;

private:
    TSharedRef<ICharacterBattleDelegate> Character;
};
