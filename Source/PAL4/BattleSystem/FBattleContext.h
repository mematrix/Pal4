#pragma once

class FBattleSystem;

/**
 * �ṩ��ս��ʱ�ڵ�һЩ���������ݵķ��ʡ�����@see FBattleSystem
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
     * ��ǰ@see FBattleSystem��ʵ��
     */
    static const FBattleSystem* BattleSystem;
};
