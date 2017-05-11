#pragma once

#include "FPrescriptionData.h"


/**
 * 配方数据提供类
 */
class PAL4_API IPrescriptionDataProvider
{
public:
    virtual ~IPrescriptionDataProvider() = default;

    /**
     * 获取配方数据
     */
    virtual const FPrescriptionData& GetPrescriptionData(int32 id) = 0;
};
