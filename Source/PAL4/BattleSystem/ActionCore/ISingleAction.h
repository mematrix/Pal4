#pragma once

#include <SharedPointer.h>
#include <Array.h>

struct FBaseAttackModel;
struct FBaseRestorerModel;
struct FBaseStatusModel;
class ICharacterBattleDelegate;

/**
 * 攻击动作的基类。封装了每种攻击（普攻、仙术攻击、技能攻击、物品攻击等）的基本流程
 */
class PAL4_API ISingleAction
{
public:
    ISingleAction(const TSharedRef<ICharacterBattleDelegate>& attacker,
        const TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>>& charactersBeAttacked) :
        Attacker(attacker),
        CharactersBeAttacked(charactersBeAttacked)
    {
    }

    ISingleAction(const ISingleAction&) = default;
    ISingleAction& operator=(const ISingleAction&) = default;

    virtual ~ISingleAction() = default;

    virtual void BeforeDoAttack() { }
    virtual void DoAttack() = 0;
    virtual void AfterDoAttack() { }

    // 计算伤害值（不考虑人物状态，只考虑当前属性。例如忽略镜的反弹效果）
    virtual TSharedRef<FBaseAttackModel> ComputeAttackResult(ICharacterBattleDelegate&, int32) = 0;
    virtual TSharedRef<FBaseRestorerModel> ComputeRestorerResult(ICharacterBattleDelegate&, int32) = 0;
    virtual TSharedRef<FBaseStatusModel> ComputeStatusResutl(ICharacterBattleDelegate&, int32) = 0;

protected:
    TSharedRef<ICharacterBattleDelegate> Attacker;
    TSharedRef<TArray<TSharedRef<ICharacterBattleDelegate>>> CharactersBeAttacked;
};
