#pragma once

#include "../IDataProviderManager.h"
#include "FDataProvider.h"


/**
 * @code IDataProviderManager \endcode 实现类。本实现类似句柄
 */
class PAL4_API FDataProviderManager : public IDataProviderManager
{
public:
    FDataProviderManager() : DataProvider(MakeShared<FDataProvider>())
    {
    }

    const TSharedRef<IRoleDataProvider>& GetRoleDataProvider() const override final { return DataProvider; }

    const TSharedRef<IMonsterDataProvider>& GetMonsterDataProvider() const override final { return DataProvider; }

    const TSharedRef<ISkillDataProvider>& GetSkillDataProvider() const override final { return DataProvider; }

    const TSharedRef<IPropDataProvider>& GetPropDataProvider() const override final { return DataProvider; }

    const TSharedRef<IEquipDataProvider>& GetEquipDataProvider() const override final { return DataProvider; }

    const TSharedRef<IPrescriptionDataProvider>& GetPrescriptionDataProvider() const override final { return DataProvider; }

private:
    TSharedRef<FDataProvider> DataProvider;
};
