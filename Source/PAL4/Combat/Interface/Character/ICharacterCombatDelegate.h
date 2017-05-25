#pragma once

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class ISingleAction;
class IRoundActionHandler;
class ICharacterStatusProperty;
class ICharacterCombatContext;
class ICharacterProperty;


/**
 * 人物战斗代理基类。作为一个代理，在战斗过程中，提供对人物属性的访问和设置接口；
 * 同时提供战斗过程中需要的信息和回调控制接口
 */
class PAL4_API ICharacterCombatDelegate
{
public:
    ICharacterCombatDelegate() : Context(nullptr)
    {
    }

    ICharacterCombatDelegate(const ICharacterCombatDelegate&) = default;
    ICharacterCombatDelegate(ICharacterCombatDelegate&&) = default;
    
    ICharacterCombatDelegate& operator=(const ICharacterCombatDelegate&) = default;
    ICharacterCombatDelegate& operator=(ICharacterCombatDelegate&&) = default;

    virtual ~ICharacterCombatDelegate() = default;


    void BeginBattle(ICharacterCombatContext& context)
    {
        _ASSERT(!Context);
        Context = &context;
        OnBattleBegin();
    }

    void FinishBattle()
    {
        OnBattleFinished();
        Context = nullptr;
    }

    ICharacterCombatContext* GetContext() const { return Context; }

    virtual ICharacterProperty& GetProperty() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnAttackActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseAttackModel&, int32) = 0;

    virtual void OnRestorerActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseRestorerModel&, int32) = 0;

    virtual void OnStatusActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseStatusModel&, int32) = 0;

    /**
     * 角色是否是由玩家控制的一方，true表示玩家一方，false表示敌方（即AI怪物）
     */
    virtual bool IsPlayer() const = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICharacterCombatContext* Context;
};
