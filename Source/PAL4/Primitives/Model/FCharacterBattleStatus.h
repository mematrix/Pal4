#pragma once

#include "../EnumType/ECharacterBattleStatus.h"


// Buff״̬
struct PAL4_API FCharacterBattleStatus
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

    FCharacterBattleStatus() :
        CommonBuff(ECommonBuff::None),
        Poison(EPoison::None),
        ControlledDebuff(EControlledDebuff::None),
        IsInvisible(false),
        CanRevive(false)
    {
    }
};
