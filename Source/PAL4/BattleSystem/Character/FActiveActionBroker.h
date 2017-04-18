#pragma once

#include "Core/FakeDynamicDelegate.h"

#include "../ActionCore/ISingleAction.h"

class FBattleCharacter;


class PAL4_API FActiveActionBroker
{
public:
    typedef FakeDynamicDelegate<TSharedRef<FBaseAttackModel>(ISingleAction::*)(ICharacterBattleDelegate&, int32)> FAttackComDelegate;
    typedef FakeDynamicDelegate<TSharedRef<FBaseRestorerModel>(ISingleAction::*)(ICharacterBattleDelegate&, int32)> FRestorerComDelegate;
    typedef FakeDynamicDelegate<TSharedRef<FBaseStatusModel>(ISingleAction::*)(ICharacterBattleDelegate&, int32)> FStatusComDelegate;

    FActiveActionBroker();

    ICharacterBattleDelegate* GetActiveCharacter() const { return ActiveCharacter; }
    FBattleCharacter* GetPassiveCharacter() const { return PassiveCharacter; }

    const FAttackComDelegate& GetAttackDelegate() const { return AttackComDelegate; }
    const FRestorerComDelegate& GetRestorerDelegate() const { return RestorerComDelegate; }
    const FStatusComDelegate& GetStatusDelegate() const { return StatusComDelegate; }

    void SetCharacter(ICharacterBattleDelegate& active, FBattleCharacter& passive)
    {
        ActiveCharacter = &active;
        PassiveCharacter = &passive;
    }

private:
    // 攻击者，可删除？
    ICharacterBattleDelegate* ActiveCharacter;
    // 被攻击者
    FBattleCharacter* PassiveCharacter;

    FAttackComDelegate AttackComDelegate;
    FRestorerComDelegate RestorerComDelegate;
    FStatusComDelegate StatusComDelegate;
};
