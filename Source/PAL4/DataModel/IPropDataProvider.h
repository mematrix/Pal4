#pragma once

#include "FPropData.h"


class PAL4_API IPropDataProvider
{
public:
    virtual ~IPropDataProvider() = default;

    /**
     * 获取道具信息
     */
    virtual const FPropData& GetPropData(int32 id) = 0;
};
