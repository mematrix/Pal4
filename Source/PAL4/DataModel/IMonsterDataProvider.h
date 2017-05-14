#pragma once

#include "FMonsterData.h"


/**
 * 怪物属性数据提供类
 */
class PAL4_API IMonsterDataProvider
{
public:
    virtual ~IMonsterDataProvider() = default;

    /**
     * 获取指定ID的怪物属性
     */
    virtual const FMonsterData& GetMonsterData(int32 id) const = 0;
};
