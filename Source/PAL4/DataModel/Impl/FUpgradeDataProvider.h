#pragma once

#include "../IUpgradeDataProvider.h"


/**
 * @code IUpgradeDataProvider \endcode 实现类。（预计）初始化时从sqlite读取数据
 */
class PAL4_API FUpgradeDataProvider : public IUpgradeDataProvider
{
public:
    const std::vector<FUpgradeData>& GetRoleData(int32 id) override;

    const FUpgradeData& GetRoleLevelData(int32 id, int32 level) override;

    int32 ComputeLevelByExperience(int32 id, int32 exp) override;

    int32 GetLeastExperienceOfLevel(int32 id, int32 level) override;

    int32 GetExperienceOfLevel(int32 id, int32 level) override;
};
