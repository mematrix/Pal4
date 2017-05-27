#pragma once

#include "../IDataProviderManager.h"
#include "FDataProvider.h"


/**
 * @code IDataProviderManager \endcode ʵ���ࡣ��ʵ�����ƾ��
 */
class PAL4_API FDataProviderManager : public IDataProviderManager
{
public:
    FDataProviderManager() : DataProvider()
    {
    }

    const IRoleDataProvider& GetRoleDataProvider() const override final { return DataProvider; }

    const IMonsterDataProvider& GetMonsterDataProvider() const override final { return DataProvider; }

    const ISkillDataProvider& GetSkillDataProvider() const override final { return DataProvider; }

    const IPropDataProvider& GetPropDataProvider() const override final { return DataProvider; }

    const IEquipDataProvider& GetEquipDataProvider() const override final { return DataProvider; }

    const IPrescriptionDataProvider& GetPrescriptionDataProvider() const override final { return DataProvider; }

private:
    FDataProvider DataProvider;
};
