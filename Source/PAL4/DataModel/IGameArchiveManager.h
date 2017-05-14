#pragma once

#include <SharedPointer.h>

#include "Core/IEnumerator.h"
#include "FGameArchive.h"


/**
 * ��Ϸ�浵�����ࡣ��֪֧��100���浵λ��
 */
class PAL4_API IGameArchiveManager
{
public:
    typedef TSharedPtr<IEnumerator<FGameArchive>> ArchiveEnumerator;
    typedef TSharedPtr<IEnumerator<const FGameArchive>> ArchiveConstEnumerator;

    virtual ~IGameArchiveManager() = default;

    /**
     * ��ȡָ�������Ĵ浵���ݡ����ָ�����������޴浵��������nullptr
     * @exception std::out_of_range index����[0, 100)��Χʱ�׳�
     */
    virtual TSharedPtr<FGameArchive> ReadArchive(int32 index) const = 0;

    /**
     * ��ȡ�浵���ݵ�����
     */
    virtual ArchiveEnumerator GetEnumerator() = 0;

    /**
     * ��ȡ�浵���ݵ�����
     */
    virtual ArchiveConstEnumerator GetEnumerator() const = 0;

    /**
     * д��һ���浵��ָ�����������ָ�������Ѵ��ڴ浵�����ᱻ����
     * @exception std::out_of_range index����[0, 100)��Χʱ�׳�
     */
    virtual bool WriteArchive(int32 index, const FGameArchive&) = 0;
};
