#pragma once

#include "FMonsterData.h"


/**
 * �������������ṩ��
 */
class PAL4_API IMonsterDataProvider
{
public:
    virtual ~IMonsterDataProvider() = default;

    /**
     * ��ȡָ��ID�Ĺ�������
     */
    virtual const FMonsterData& GetMonsterData(int32 id) const = 0;
};
