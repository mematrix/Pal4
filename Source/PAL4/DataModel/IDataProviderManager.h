#pragma once

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

    virtual const IRoleDataProvider& GetRoleDataProvider() const = 0;

    virtual const IMonsterDataProvider& GetMonsterDataProvider() const = 0;

    virtual const ISkillDataProvider& GetSkillDataProvider() const = 0;

    virtual const IPropDataProvider& GetPropDataProvider() const = 0;

    virtual const IEquipDataProvider& GetEquipDataProvider() const = 0;

    virtual const IPrescriptionDataProvider& GetPrescriptionDataProvider() const = 0;
};
