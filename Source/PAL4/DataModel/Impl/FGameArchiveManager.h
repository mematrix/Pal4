#pragma once

#include "../IGameArchiveManager.h"


/**
 * @code IGameArchiveManager \endcode 实现类。实现存档管理
 */
class PAL4_API FGameArchiveManager : public IGameArchiveManager
{
public:
    TSharedPtr<FGameArchive> ReadArchive(int32 index) const override;

    ArchiveEnumerator GetEnumerator() override;

    ArchiveConstEnumerator GetEnumerator() const override;

    bool WriteArchive(int32 index, const FGameArchive&) override;
};
