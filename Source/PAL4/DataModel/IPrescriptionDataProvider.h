#pragma once

#include "FPrescriptionData.h"


/**
 * �䷽�����ṩ��
 */
class PAL4_API IPrescriptionDataProvider
{
public:
    virtual ~IPrescriptionDataProvider() = default;

    /**
     * ��ȡ�䷽����
     */
    virtual const FPrescriptionData& GetPrescriptionData(int32 id) = 0;
};
