#pragma once

#include <SharedPointer.h>

class IRoleDataProvider;


/**
 * 数据提供类型的管理类。可访问各种数据（来源于数据库、保存文档等）
 */
class PAL4_API FDataProviderManager
{
public:
    // TODO: 需要改成非静态方法调用
    static TSharedRef<IRoleDataProvider> GetUpgradeDataProvider();
};
