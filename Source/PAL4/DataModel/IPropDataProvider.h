#pragma once

#include "FPropData.h"


/**
 * ������Ϣ�ṩ��
 */
class PAL4_API IPropDataProvider
{
public:
    virtual ~IPropDataProvider() = default;

    /**
     * ��ȡ������Ϣ
     */
    virtual const FPropData& GetPropData(int32 id) const = 0;
};
