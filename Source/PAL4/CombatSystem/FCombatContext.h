#pragma once

#include "FCombatSystem.h"


/**
 * �ṩ��ս��ʱ�ڵ�һЩ���������ݵķ��ʡ�����@see FCombatSystem
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
     * ��ǰ@see FBattleSystem��ʵ��
     */
    static const FCombatSystem* BattleSystem;
};
