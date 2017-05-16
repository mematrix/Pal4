#pragma once

#include <SharedPointer.h>

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

    virtual const TSharedRef<IRoleDataProvider>& GetRoleDataProvider() const = 0;

    virtual const TSharedRef<IMonsterDataProvider>& GetMonsterDataProvider() const = 0;

    virtual const TSharedRef<ISkillDataProvider>& GetSkillDataProvider() const = 0;

    virtual const TSharedRef<IPropDataProvider>& GetPropDataProvider() const = 0;

    virtual const TSharedRef<IEquipDataProvider>& GetEquipDataProvider() const = 0;

    virtual const TSharedRef<IPrescriptionDataProvider>& GetPrescriptionDataProvider() const = 0;
};
