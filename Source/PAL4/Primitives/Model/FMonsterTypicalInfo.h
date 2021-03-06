#pragma once

#include <Platform.h>

#include "../EnumType/EImmune.h"


struct PAL4_API FMonsterTypicalInfo
{
    // 反击率追加
    int32 HitbackRate;
    // 免疫信息
    int32 ImmuneFlags;

    bool GetImmuneInfo(EImmune info) const { return ImmuneFlags & static_cast<int32>(info); }

    void SetImmuneInfo(EImmune info) { ImmuneFlags |= static_cast<int32>(info); }
};
