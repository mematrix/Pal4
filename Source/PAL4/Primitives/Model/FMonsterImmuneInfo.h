#pragma once

#include <Platform.h>

#include "../EnumType/EImmune.h"


struct PAL4_API FMonsterImmuneInfo
{
    int32 ImmuneInfo;

    bool GetImmuneInfo(EImmune info) const { return ImmuneInfo & static_cast<int32>(info); }

    void SetImmuneInfo(EImmune info) { ImmuneInfo |= static_cast<int32>(info); }
};
