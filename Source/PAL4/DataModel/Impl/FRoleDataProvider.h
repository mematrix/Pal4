#pragma once

#include "../IRoleDataProvider.h"


/**
 * @code IRoleDataProvider \endcode ʵ���ࡣ��Ԥ�ƣ���ʼ��ʱ��sqlite��ȡ����
 */
class PAL4_API FRoleDataProvider : public IRoleDataProvider
{
public:
    const FRoleData& GetRoleBaseData(int32 id) override;

    const std::vector<FUpgradeData>& GetRoleAllData(int32 id) override;

    const FUpgradeData& GetRoleLevelData(int32 id, int32 level) override;

    int32 ComputeLevelByExperience(int32 id, int32 exp) override;

    int32 GetLeastExperienceOfLevel(int32 id, int32 level) override;

    int32 GetExperienceOfLevel(int32 id, int32 level) override;
};
