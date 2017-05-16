#pragma once

#include "FEquipData.h"


/**
 * 装备属性信息提供类
 */
class PAL4_API IEquipDataProvider
{
public:
    virtual ~IEquipDataProvider() = default;

    /**
     * 获取装备信息
     */
    virtual const FEquipData& GetEquipData(int32 id) const = 0;
};
