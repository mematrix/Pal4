#pragma once

#include "FMagicData.h"
#include "FStuntData.h"


/**
 * ����������Ϣ�ṩ��
 */
class PAL4_API ISkillDataProvider
{
public:
    virtual ~ISkillDataProvider() = default;

    /**
     * ��ȡָ��������Ϣ
     */
    virtual const FMagicData& GetMagicData(int32 id) = 0;

    /**
     * ��ȡָ���ؼ���Ϣ
     */
    virtual const FStuntData& GetStuntData(int32 id) = 0;
};
