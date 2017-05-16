#pragma once

#include "FEquipData.h"


/**
 * װ��������Ϣ�ṩ��
 */
class PAL4_API IEquipDataProvider
{
public:
    virtual ~IEquipDataProvider() = default;

    /**
     * ��ȡװ����Ϣ
     */
    virtual const FEquipData& GetEquipData(int32 id) const = 0;
};
