#pragma once

#include "../IGameArchiveManager.h"


/**
 * @code IGameArchiveManager \endcode ʵ���ࡣʵ�ִ浵����
 */
class PAL4_API FGameArchiveManager : public IGameArchiveManager
{
public:
    TSharedPtr<FGameArchive> ReadArchive(int32 index) const override;

    ArchiveEnumerator GetEnumerator() override;

    ArchiveConstEnumerator GetEnumerator() const override;

    bool WriteArchive(int32 index, const FGameArchive&) override;
};
