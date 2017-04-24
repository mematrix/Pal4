#pragma once

#include "FCombatSystem.h"


/**
 * 提供对战斗时期的一些上下文内容的访问。例如@see FCombatSystem
 */
class PAL4_API FCombatContext
{
    friend class FCombatSystem;

public:
    static const FCombatSystem* GetBattleSystem()
    {
        return BattleSystem;
    }

private:
    static void SetBattleSystem(const FCombatSystem* battleSystem)
    {
        BattleSystem = battleSystem;
    }

private:
    /**
     * 当前@see FBattleSystem的实例
     */
    static const FCombatSystem* BattleSystem;
};
