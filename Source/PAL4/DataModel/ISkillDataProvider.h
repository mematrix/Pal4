#pragma once

#include "FMagicData.h"
#include "FStuntData.h"


/**
 * 技能属性信息提供类
 */
class PAL4_API ISkillDataProvider
{
public:
    virtual ~ISkillDataProvider() = default;

    /**
     * 获取指定仙术信息
     */
    virtual const FMagicData& GetMagicData(int32 id) = 0;

    /**
     * 获取指定特技信息
     */
    virtual const FStuntData& GetStuntData(int32 id) = 0;
};
