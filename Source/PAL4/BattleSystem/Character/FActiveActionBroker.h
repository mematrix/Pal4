#pragma once

#include "Core/FakeDynamicDelegate.h"

class ISingleAction;
class FBattleCharacter;


class PAL4_API FActiveActionBroker
{
public:
    typedef FakeDynamicDelegate<TSharedRef<FBaseAttackModel>(ISingleAction::*)(const ICharacterBattleDelegate&, int32) const> FAttackComDelegate;
    typedef FakeDynamicDelegate<TSharedRef<FBaseRestorerModel>(ISingleAction::*)(const ICharacterBattleDelegate&, int32) const> FRestorerComDelegate;
    typedef FakeDynamicDelegate<TSharedRef<FBaseStatusModel>(ISingleAction::*)(const ICharacterBattleDelegate&, int32) const> FStatusComDelegate;

    FActiveActionBroker();

    FBattleCharacter* GetPassiveCharacter() const { return PassiveCharacter; }

    const FAttackComDelegate& GetAttackDelegate() const { return AttackComDelegate; }
    const FRestorerComDelegate& GetRestorerDelegate() const { return RestorerComDelegate; }
    const FStatusComDelegate& GetStatusDelegate() const { return StatusComDelegate; }

    void SetCharacter(FBattleCharacter& passive) { PassiveCharacter = &passive; }

private:
    // ±»¹¥»÷Õß
    FBattleCharacter* PassiveCharacter;

    FAttackComDelegate AttackComDelegate;
    FRestorerComDelegate RestorerComDelegate;
    FStatusComDelegate StatusComDelegate;
};
