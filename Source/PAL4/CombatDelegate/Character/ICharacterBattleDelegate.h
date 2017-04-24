#pragma once

#include <Delegate.h>

#include "Util/MacroUtil.h"
#include "CharacterPrimitives/Model/ECharacterBasicType.h"

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class ISingleAction;
class IRoundActionHandler;
class ICharacterPropertyManager;
class FCharacterPersistentStatus;
class ICharacterBattleContext;


/*
 * 人物战斗代理基类。作为一个代理，在战斗过程中，提供对人物属性的访问和设置接口；
 * 同时提供战斗过程中需要的信息和回调控制接口
 */
class PAL4_API ICharacterBattleDelegate
{
public:
    DECLARE_EVENT_TwoParams(ICharacterBattleDelegate, FOnPropertyChangedEvent, const ICharacterBattleDelegate&, ECharacterBasicType)
    DECLARE_EVENT_OneParam(ICharacterBattleDelegate, FOnCharacterDeadEvent, const ICharacterBattleDelegate&)
    DECLARE_EVENT_OneParam(ICharacterBattleDelegate, FOnCharacterReviveEvent, const ICharacterBattleDelegate&)

protected:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnCharacterDeadEvent OnCharacterDeadEvent;
    FOnCharacterReviveEvent OnCharacterReviveEvent;

public:
    ICharacterBattleDelegate() : Context(nullptr)
    {
    }

    MAKE_DEFAULT_COPY_MOVE_CTOR_AND_OP(ICharacterBattleDelegate)

    virtual ~ICharacterBattleDelegate() = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnCharacterDeadEvent& OnCharacterDead() { return OnCharacterDeadEvent; }
    FOnCharacterReviveEvent& OnCharacterRevive() { return OnCharacterReviveEvent; }

    void BeginBattle(ICharacterBattleContext& context)
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

    ICharacterBattleContext* GetContext() const { return Context; }

    virtual ICharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterPersistentStatus& GetPersistentStatus() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnAttackActionFinished(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseAttackModel&, int32) = 0;

    virtual void OnRestorerActionFinished(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseRestorerModel&, int32) = 0;

    virtual void OnStatusActionFinished(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseStatusModel&, int32) = 0;

    /**
     * 角色是否是由玩家控制的一方，true表示玩家一方，false表示敌方（即AI怪物）
     */
    virtual bool IsPlayer() const = 0;
    /**
     * 角色是否存活
     */
    virtual bool IsAlive() const = 0;
    /*
     * 获取角色唯一ID，用于从全局数据集中获取角色信息，例如头像、名称等
     */
    virtual int32 GetId() const = 0;

    /**
     * 获取角色生命值
     */
    virtual int32 GetHealthValue() const = 0;
    /**
     * 获取角色神属性的值
     */
    virtual int32 GetManaValue() const = 0;
    /**
     * 获取角色气属性的值
     */
    virtual int32 GetCraftValue() const = 0;

    /**
     * 增加或减少角色生命值。值为正数表示增加，负数表示减少
     * @return 实际增加或减少的生命值
     */
    virtual int32 AddHealthValue(int32) = 0;
    /**
     * 增加或减少角色神属性值。值为正数表示增加，负数表示减少
     * @return 实际增加或减少的神属性值
     */
    virtual int32 AddManaValue(int32) = 0;
    /**
     * 增加或减少角色气属性值。值为正数表示增加，负数表示减少
     * @return 实际增加或减少的气属性值
     */
    virtual int32 AddCraftValue(int32) = 0;

    /**
     * 获取指定类别的仙术属性点数
     * @return 指定系仙术的属性点数
     */
    virtual int32 GetMagicPoint(EMagicCategory) = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICharacterBattleContext* Context;
};
