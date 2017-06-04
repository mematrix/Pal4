#pragma once

#include <crtdbg.h>

class ICombatContext;
class ICharacterProperty;
class IRoundActionHandler;


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

    /**
     * 角色是否是由玩家控制的一方，true表示玩家一方，false表示敌方（即AI怪物）
     */
    virtual bool IsPlayer() const = 0;

    /**
     * 获取角色属性。如果角色为玩家控制人物，实际返回@code IRoleProperty \endcode 对象，
     * 而当角色为AI时，返回@code IMonsterProperty \endcode 对象
     */
    virtual ICharacterProperty& GetProperty() = 0;

    /**
     * 获取回合动作处理对象
     */
    virtual IRoundActionHandler& GetRoundAction() = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICombatContext* Context;
};
