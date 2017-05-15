#pragma once

#include "../IRoleDataProvider.h"
#include "../IMonsterDataProvider.h"
#include "../ISkillDataProvider.h"
#include "../IPropDataProvider.h"
#include "../IEquipDataProvider.h"
#include "../IPrescriptionDataProvider.h"


/**
 * 数据层实现类。（预计）初始化时从sqlite读取数据。\n
 * 实现以下接口：\n
 * @code IRoleDataProvider \endcode \n
 * @code IMonsterDataProvider \endcode \n
 * @code ISkillDataProvider \endcode \n
 * @code IPropDataProvider \endcode \n
 * @code IEquipDataProvider \endcode \n
 * @code IPrescriptionDataProvider \endcode \n
 */
class PAL4_API FDataProvider
    : public IRoleDataProvider, 
    public IMonsterDataProvider, 
    public ISkillDataProvider,
    public IPropDataProvider,
    public IEquipDataProvider,
    public IPrescriptionDataProvider
{
public:
    const FRoleData& GetRoleBaseData(int32 id) const override;

    const std::vector<FUpgradeData>& GetRoleAllData(int32 id) const override;

    const FUpgradeData& GetRoleLevelData(int32 id, int32 level) const override;

    int32 ComputeLevelByExperience(int32 id, int32 exp) const override;

    int32 GetLeastExperienceOfLevel(int32 id, int32 level) const override;

    int32 GetExperienceOfLevel(int32 id, int32 level) const override;

    const FMonsterData& GetMonsterData(int32 id) const override;

    const FMagicData& GetMagicData(int32 id) const override;

    const FStuntData& GetStuntData(int32 id) const override;

    const FPropData& GetPropData(int32 id) const override;

    const FEquipData& GetEquipData(int32 id) override;

    const FPrescriptionData& GetPrescriptionData(int32 id) const override;
};
