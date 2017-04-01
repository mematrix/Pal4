#pragma once

class FBattleSystem;

/**
 * 提供对战斗时期的一些上下文内容的访问。例如@see FBattleSystem
 */
class PAL4_API FBattleContext
{
    friend class FBattleSystem;

public:
    static const FBattleSystem* GetBattleSystem()
    {
        return BattleSystem;
    }

private:
    static void SetBattleSystem(const FBattleSystem* battleSystem)
    {
        BattleSystem = battleSystem;
    }

private:
    /**
     * 当前@see FBattleSystem的实例
     */
    static const FBattleSystem* BattleSystem;
};
