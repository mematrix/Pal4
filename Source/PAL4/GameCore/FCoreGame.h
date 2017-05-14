#pragma once

#include <SharedPointer.h>

class IGameArchiveManager;
class IDataProviderManager;


class PAL4_API FCoreGame
{
public:
    static FCoreGame& SharedInstance();

private:
    FCoreGame();

public:
    IGameArchiveManager& GetArchiveManager();
    IDataProviderManager& GetDataProviderManager();

private:
    TSharedRef<IGameArchiveManager> ArchiveManager;
    TSharedRef<IDataProviderManager> DataProviderManager;
};
