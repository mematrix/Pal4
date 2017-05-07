#pragma once

#include "../EnumType/ECombatStatus.h"


// Buff状态
struct PAL4_API FCombatStatus
{
    // 通用Buff：镜壁界宁
    ECommonBuff CommonBuff;
    // 中毒状态
    EPoison Poison;
    // 控制性Debuff
    EControlledDebuff ControlledDebuff;
    // 是否隐身状态
    bool IsInvisible;
    // 是否可在死亡后立即复活。“生”状态
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
