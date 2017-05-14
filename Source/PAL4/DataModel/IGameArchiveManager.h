#pragma once

#include <SharedPointer.h>

#include "Core/IEnumerator.h"
#include "FGameArchive.h"


/**
 * 游戏存档管理类。已知支持100个存档位置
 */
class PAL4_API IGameArchiveManager
{
public:
    typedef TSharedPtr<IEnumerator<FGameArchive>> ArchiveEnumerator;
    typedef TSharedPtr<IEnumerator<const FGameArchive>> ArchiveConstEnumerator;

    virtual ~IGameArchiveManager() = default;

    /**
     * 读取指定索引的存档数据。如果指定索引处尚无存档，将返回nullptr
     * @exception std::out_of_range index不在[0, 100)范围时抛出
     */
    virtual TSharedPtr<FGameArchive> ReadArchive(int32 index) const = 0;

    /**
     * 获取存档数据迭代器
     */
    virtual ArchiveEnumerator GetEnumerator() = 0;

    /**
     * 获取存档数据迭代器
     */
    virtual ArchiveConstEnumerator GetEnumerator() const = 0;

    /**
     * 写入一个存档到指定索引，如果指定索引已存在存档，将会被覆盖
     * @exception std::out_of_range index不在[0, 100)范围时抛出
     */
    virtual bool WriteArchive(int32 index, const FGameArchive&) = 0;
};
