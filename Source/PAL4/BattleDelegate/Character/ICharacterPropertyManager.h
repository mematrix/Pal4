#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "CharacterPrimitives/Model/ECharacterBasicType.h"

class PAL4_API ICharacterPropertyManager
{
public:
    DECLARE_EVENT_TwoParams(ICharacterPropertyManager, FOnPropertyChangedEvent, const ICharacterPropertyManager&, ECharacterBasicType)
    DECLARE_EVENT_OneParam(ICharacterPropertyManager, FOnCharacterDeadEvent, const ICharacterPropertyManager&)
    DECLARE_EVENT_OneParam(ICharacterPropertyManager, FOnCharacterReviveEvent, const ICharacterPropertyManager&)

protected:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnCharacterDeadEvent OnCharacterDeadEvent;
    FOnCharacterReviveEvent OnCharacterReviveEvent;

public:
    ICharacterPropertyManager() = default;
    ICharacterPropertyManager(const ICharacterPropertyManager&) = default;
    ICharacterPropertyManager(ICharacterPropertyManager&&) = default;

    virtual ~ICharacterPropertyManager() { }

    ICharacterPropertyManager& operator=(const ICharacterPropertyManager&) = default;
    ICharacterPropertyManager& operator=(ICharacterPropertyManager&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnCharacterDeadEvent& OnCharacterDead() { return OnCharacterDeadEvent; }
    FOnCharacterReviveEvent& OnCharacterRevive() { return OnCharacterReviveEvent; }

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
};

