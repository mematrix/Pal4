#pragma once

#include "ECharacterBattleStatus.h"

struct PAL4_API FCharacterBattleStatus
{
    // Buff״̬
    // ͨ��Buff�����ڽ���
    ECommonBuff CommonBuff;
    // �ж�״̬
    EPoison Poison;
    // ������Debuff
    EControlledDebuff ControlledDebuff;
    // �Ƿ�����״̬
    bool IsInvisible;
    // �Ƿ�����������������������״̬
    bool CanRevive;
};
