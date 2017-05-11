#pragma once

#include <vector>

#include "FRoleData.h"
#include "FUpgradeData.h"


/**
 * 角色属性数据提供类
 */
class PAL4_API IRoleDataProvider
{
public:
    virtual ~IRoleDataProvider() = default;

    /**
     * 获取指定角色固有属性信息
     */
    virtual const FRoleData& GetRoleBaseData(int32 id) = 0;

    /**
     * 获取指定角色所有等级数据
     */
    virtual const std::vector<FUpgradeData>& GetRoleAllData(int32 id) = 0;

    /**
     * 获取指定等级的基础属性数据
     */
    virtual const FUpgradeData& GetRoleLevelData(int32 id, int32 level) = 0;

    /**
     * 计算指定经验值对应的等级
     */
    virtual int32 ComputeLevelByExperience(int32 id, int32 exp) = 0;

    /**
     * 获取一个等级所需最低经验值。例如1级需要0经验，二级需要1级升级的经验等
     */
    virtual int32 GetLeastExperienceOfLevel(int32 id, int32 level) = 0;

    /**
     * 获取一个等级升级所需全部经验值。也就是一个等级从经验0开始到下一个等级经验0所需要的经验
     */
    virtual int32 GetExperienceOfLevel(int32 id, int32 level) = 0;
};
