#pragma once

#include <vector>

#include "FUpgradeData.h"


class PAL4_API IUpgradeDataProvider
{
public:
    virtual ~IUpgradeDataProvider() = default;

    /**
     * ��ȡָ����ɫ���еȼ�����
     */
    virtual const std::vector<FUpgradeData>& GetRoleData(int32 id) = 0;

    /**
     * ��ȡָ���ȼ��Ļ�����������
     */
    virtual const FUpgradeData& GetRoleLevelData(int32 id, int32 level) = 0;

    /**
     * ����ָ������ֵ��Ӧ�ĵȼ�
     */
    virtual int32 ComputeLevelByExperience(int32 id, int32 exp) = 0;

    /**
     * ��ȡһ���ȼ�������;���ֵ������1����Ҫ0���飬������Ҫ1�������ľ����
     */
    virtual int32 GetLeastExperienceOfLevel(int32 id, int32 level) = 0;

    /**
     * ��ȡһ���ȼ���������ȫ������ֵ��Ҳ����һ���ȼ��Ӿ���0��ʼ����һ���ȼ�����0����Ҫ�ľ���
     */
    virtual int32 GetExperienceOfLevel(int32 id, int32 level) = 0;
};
