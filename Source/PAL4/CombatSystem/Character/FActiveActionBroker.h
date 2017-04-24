#pragma once

#include "Core/FakeDynamicDelegate.h"

class ISingleAction;
class FCombatCharacter;


class PAL4_API FActiveActionBroker
{
public:
    typedef FakeDynamicDelegate<TSharedRef<FBaseAttackModel>(ISingleAction::*)(const ICharacterCombatDelegate&, int32) const> FAttackComDelegate;
    typedef FakeDynamicDelegate<TSharedRef<FBaseRestorerModel>(ISingleAction::*)(const ICharacterCombatDelegate&, int32) const> FRestorerComDelegate;
    typedef FakeDynamicDelegate<TSharedRef<FBaseStatusModel>(ISingleAction::*)(const ICharacterCombatDelegate&, int32) const> FStatusComDelegate;

    FActiveActionBroker();

    FCombatCharacter* GetPassiveCharacter() const { return PassiveCharacter; }

    const FAttackComDelegate& GetAttackDelegate() const { return AttackComDelegate; }
    const FRestorerComDelegate& GetRestorerDelegate() const { return RestorerComDelegate; }
    const FStatusComDelegate& GetStatusDelegate() const { return StatusComDelegate; }

    void SetCharacter(FCombatCharacter& passive) { PassiveCharacter = &passive; }

private:
    // ±»¹¥»÷Õß
    FCombatCharacter* PassiveCharacter;

    FAttackComDelegate AttackComDelegate;
    FRestorerComDelegate RestorerComDelegate;
    FStatusComDelegate StatusComDelegate;
};
