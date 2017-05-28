#pragma once

#include <crtdbg.h>

#include <Platform.h>

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class ISingleAction;
class IRoundActionHandler;
class ICharacterStatus;
class ICombatContext;
class ICharacterProperty;


/**
 * 人物战斗代理基类。作为一个代理，在战斗过程中，提供对人物属性的访问和设置接口；
 * 同时提供战斗过程中需要的信息和回调控制接口
 */
class PAL4_API ICharacterDelegate
{
public:
    ICharacterDelegate() : Context(nullptr)
    {
    }

    ICharacterDelegate(const ICharacterDelegate&) = default;
    ICharacterDelegate(ICharacterDelegate&&) = default;
    
    ICharacterDelegate& operator=(const ICharacterDelegate&) = default;
    ICharacterDelegate& operator=(ICharacterDelegate&&) = default;

    virtual ~ICharacterDelegate() = default;


    void BeginBattle(ICombatContext& context)
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

    ICombatContext* GetContext() const { return Context; }

    virtual ICharacterProperty& GetProperty() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnAttackActionFinished(const ISingleAction&, const ICharacterDelegate&, const FBaseAttackModel&, int32) = 0;

    virtual void OnRestorerActionFinished(const ISingleAction&, const ICharacterDelegate&, const FBaseRestorerModel&, int32) = 0;

    virtual void OnStatusActionFinished(const ISingleAction&, const ICharacterDelegate&, const FBaseStatusModel&, int32) = 0;

    /**
     * 角色是否是由玩家控制的一方，true表示玩家一方，false表示敌方（即AI怪物）
     */
    virtual bool IsPlayer() const = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICombatContext* Context;
};
