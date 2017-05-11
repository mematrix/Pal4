#pragma once

#include "../IRoleDataProvider.h"


/**
 * @code IRoleDataProvider \endcode 实现类。（预计）初始化时从sqlite读取数据
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
