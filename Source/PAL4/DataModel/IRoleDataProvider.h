#pragma once

#include <vector>

#include "FRoleData.h"
#include "FUpgradeData.h"


/**
 * ��ɫ���������ṩ��
 */
class PAL4_API IRoleDataProvider
{
public:
    virtual ~IRoleDataProvider() = default;

    /**
     * ��ȡָ����ɫ����������Ϣ
     */
    virtual const FRoleData& GetRoleBaseData(int32 id) = 0;

    /**
     * ��ȡָ����ɫ���еȼ�����
     */
    virtual const std::vector<FUpgradeData>& GetRoleAllData(int32 id) = 0;

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
