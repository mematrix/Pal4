#pragma once

#include "../EnumType/ECombatStatus.h"


// Buff״̬
struct PAL4_API FCombatStatus
{
    // ͨ��Buff�����ڽ���
    EBuff CommonBuff;
    // �ж�״̬
    EPoison Poison;
    // ������Debuff
    EDebuff ControlledDebuff;
    // �Ƿ�����״̬
    bool IsInvisible;
    // �Ƿ�����������������������״̬
    bool CanRevive;

    FCombatStatus() :
        CommonBuff(EBuff::None),
        Poison(EPoison::None),
        ControlledDebuff(EDebuff::None),
        IsInvisible(false),
        CanRevive(false)
    {
    }
};
