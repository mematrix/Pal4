#pragma once

#include <Delegate.h>

#include "Core/ValueTransformer.h"
#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/Model/FCharacterStatusInfo.h"


class PAL4_API ICharacterStatus
{
public:
    /**
     * ������ֵ�����仯ʱ���á��ڶ�������ָʾ�仯���������ͣ�������@code ECharacterStatusType::PropertyEnd \endcode��
     * ��˵���ж�����Է����˱仯��
     */
    DECLARE_EVENT_TwoParams(ICharacterStatus, FOnPropertyChangedEvent, const ICharacterStatus&, ECharacterStatusType)

    using FStatusTransformer = ValueTransformer<int32, ECharacterStatusType, int32, int32>;
    typedef std::function<int32(int32)> FTransformAction;

private:
    mutable FOnPropertyChangedEvent OnPropertyChangedEvent;

protected:
    void NotifyPropertyChanged(ECharacterStatusType type) const
    {
        if (OnPropertyChangedEvent.IsBound())
        {
            OnPropertyChangedEvent.Broadcast(*this, type);
        }
    }

public:
    ICharacterStatus() = default;
    ICharacterStatus(const ICharacterStatus&) = default;
    ICharacterStatus(ICharacterStatus&&) = default;

    virtual ~ICharacterStatus() = default;

    ICharacterStatus& operator=(const ICharacterStatus&) = default;
    ICharacterStatus& operator=(ICharacterStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() const { return OnPropertyChangedEvent; }

    /**
     * ����ָ�����������Ͳ�ѯ��Ӧ����ֵ�������������ٷ�������
     * @param type Ҫ��ѯ����������
     */
    virtual int32 GetPropertyValue(ECharacterStatusType type) const = 0;

    /**
     * ��ȡ����������������Ϣ
     */
    virtual const FCharacterStatusInfo& GetAccumulatedInfo() const = 0;

    /**
     * @brief ����ָ�����Ե�ֵ
     * @param type ��Ҫ����ֵ������
     */
    virtual void UpdatePropertyValue(ECharacterStatusType type) = 0;

    /**
     * @brief ����ȫ�����Ե�ֵ
     */
    virtual void UpdateAllProperties() = 0;

    void AddTransformer(int32 key, ECharacterStatusType type, const FTransformAction& func)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.AddTransformer(key, type, func);
        UpdatePropertyValue(type);
    }

    void AddOrUpdateTransformer(int32 key, ECharacterStatusType type, const FTransformAction& func)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.RemoveTransformer(key, type);
        Transformer.AddTransformer(key, type, func);
        UpdatePropertyValue(type);
    }

    void RemoveTransformer(int32 key, ECharacterStatusType type)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.RemoveTransformer(key, type);
        UpdatePropertyValue(type);
    }

    void RemoveTransformerByKey(int32 key)
    {
        Transformer.RemoveKey(key);
        UpdateAllProperties();
    }

    void RemoveTransformerByStatus(ECharacterStatusType type)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.RemoveGroup(type);
        UpdatePropertyValue(type);
    }

protected:
    FStatusTransformer Transformer;
};
