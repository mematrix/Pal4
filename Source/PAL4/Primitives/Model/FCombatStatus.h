#pragma once

#include "../EnumType/ECombatStatus.h"


// Buff״̬
struct PAL4_API FCombatStatus
{
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

    FCombatStatus() :
        CommonBuff(ECommonBuff::None),
        Poison(EPoison::None),
        ControlledDebuff(EControlledDebuff::None),
        IsInvisible(false),
        CanRevive(false)
    {
    }
};
