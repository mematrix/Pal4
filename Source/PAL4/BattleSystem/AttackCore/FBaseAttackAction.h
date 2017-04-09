#pragma once

#include <SharedPointer.h>
#include <Array.h>

class ICharacterBattleDelegate;

/**
 * 攻击动作的基类。封装了每种攻击（普攻、仙术攻击、技能攻击、物品攻击等）的基本流程
 */
class PAL4_API FBaseAttackAction
{
public:
    FBaseAttackAction(const TSharedRef<ICharacterBattleDelegate>& attacker,
        const TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>>& charactersBeAttacked) :
        Attacker(attacker),
        CharactersBeAttacked(charactersBeAttacked)
    {
    }

    FBaseAttackAction(const FBaseAttackAction&) = default;
    FBaseAttackAction& operator=(const FBaseAttackAction&) = default;

    virtual ~FBaseAttackAction() = default;

    virtual void BeforeDoAttack() { }
    virtual void DoAttack() = 0;
    virtual void AfterDoAttack() { }

protected:
    TSharedRef<ICharacterBattleDelegate> Attacker;
    TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>> CharactersBeAttacked;
};
