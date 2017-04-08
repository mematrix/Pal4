#pragma once

#include <Platform.h>

class PAL4_API ICharacterPropertyManager
{
public:
    virtual ~ICharacterPropertyManager() { }

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
     */
    virtual void AddHealthValue(int32) = 0;
    /**
     * 增加或减少角色神属性值。值为正数表示增加，负数表示减少
     */
    virtual void AddManaValue(int32) = 0;
    /**
     * 增加或减少角色气属性值。值为正数表示增加，负数表示减少
     */
    virtual void AddCraftValue(int32) = 0;
};
