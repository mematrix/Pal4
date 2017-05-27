#pragma once

class IRoleDataProvider;
class IMonsterDataProvider;
class ISkillDataProvider;
class IPropDataProvider;
class IEquipDataProvider;
class IPrescriptionDataProvider;


/**
 * 数据提供类型的管理类。可访问各种数据（来源于数据库、保存文档等）
 */
class PAL4_API IDataProviderManager
{
public:
    virtual ~IDataProviderManager() = default;

    virtual const IRoleDataProvider& GetRoleDataProvider() const = 0;

    virtual const IMonsterDataProvider& GetMonsterDataProvider() const = 0;

    virtual const ISkillDataProvider& GetSkillDataProvider() const = 0;

    virtual const IPropDataProvider& GetPropDataProvider() const = 0;

    virtual const IEquipDataProvider& GetEquipDataProvider() const = 0;

    virtual const IPrescriptionDataProvider& GetPrescriptionDataProvider() const = 0;
};
