#pragma once

#include <SharedPointer.h>

class IRoleDataProvider;
class IMonsterDataProvider;
class ISkillDataProvider;
class IPropDataProvider;
class IEquipDataProvider;
class IPrescriptionDataProvider;


/**
 * �����ṩ���͵Ĺ����ࡣ�ɷ��ʸ������ݣ���Դ�����ݿ⡢�����ĵ��ȣ�
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
