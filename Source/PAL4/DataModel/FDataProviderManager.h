#pragma once

#include <SharedPointer.h>

class IUpgradeDataProvider;


class PAL4_API FDataProviderManager
{
public:
    static TSharedRef<IUpgradeDataProvider> GetUpgradeDataProvider();
};
