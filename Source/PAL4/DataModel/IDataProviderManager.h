#pragma once

#include <SharedPointer.h>

class IRoleDataProvider;


/**
 * �����ṩ���͵Ĺ����ࡣ�ɷ��ʸ������ݣ���Դ�����ݿ⡢�����ĵ��ȣ�
 */
class PAL4_API IDataProviderManager
{
public:
    // TODO: ��Ҫ�ĳɷǾ�̬��������
    static TSharedRef<IRoleDataProvider> GetUpgradeDataProvider();
};
