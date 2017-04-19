#pragma once

#include "Core/FakeDynamicDelegate.h"

class ISingleAction;
class FBattleCharacter;


class PAL4_API FActiveActionBroker
{
public:
    typedef FakeDynamicDelegate<TSharedRef<FBaseAttackModel>(ISingleAction::*)(ICharacterBattleDelegate&, int32)> FAttackComDelegate;
    typedef FakeDynamicDelegate<TSharedRef<FBaseRestorerModel>(ISingleAction::*)(ICharacterBattleDelegate&, int32)> FRestorerComDelegate;
    typedef FakeDynamicDelegate<TSharedRef<FBaseStatusModel>(ISingleAction::*)(ICharacterBattleDelegate&, int32)> FStatusComDelegate;

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
