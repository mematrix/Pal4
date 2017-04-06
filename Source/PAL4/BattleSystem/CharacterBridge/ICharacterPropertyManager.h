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
    /**
     * 获取角色速度值
     */
    virtual int32 GetSpeedValue() const = 0;
};
