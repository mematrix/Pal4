#pragma once

#include <SharedPointer.h>

#include "Core/IEnumerator.h"
#include "FGameArchive.h"


class PAL4_API IGameArchiveManager
{
public:
    typedef TSharedRef<IEnumerator<FGameArchive>> ArchiveEnumerator;
    typedef TSharedRef<IEnumerator<const FGameArchive>> ArchiveConstEnumerator;

    virtual ~IGameArchiveManager() = default;

    virtual TSharedRef<FGameArchive> ReadArchive(int32 index) const = 0;

    virtual ArchiveEnumerator GetEnumerator() = 0;

    virtual ArchiveConstEnumerator GetEnumerator() const = 0;

    virtual bool WriteArchive(int32 index, const FGameArchive&) = 0;
};
