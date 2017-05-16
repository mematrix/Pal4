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

    FCoreGame(const FCoreGame&) = default;
    FCoreGame& operator=(const FCoreGame&) = default;

public:
    IGameArchiveManager& GetArchiveManager() const { return ArchiveManager.Get(); }
    IDataProviderManager& GetDataProviderManager() const { return DataProviderManager.Get(); }

private:
    TSharedRef<IGameArchiveManager> ArchiveManager;
    TSharedRef<IDataProviderManager> DataProviderManager;
};
