#pragma once

#include <SharedPointer.h>

class IUpgradeDataProvider;


/**
 * �����ṩ���͵Ĺ����ࡣ�ɷ��ʸ������ݣ���Դ�����ݿ⡢�����ĵ��ȣ�
 */
class PAL4_API FDataProviderManager
{
public:
    // TODO: ��Ҫ�ĳɷǾ�̬��������
    static TSharedRef<IUpgradeDataProvider> GetUpgradeDataProvider();
};