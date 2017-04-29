#pragma once

#include <Delegate.h>

#include "Core/ValueTransformer.h"
#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/Model/FCharacterStatusInfo.h"


class PAL4_API ICharacterStatusProperty
{
public:
    /**
     * ������ֵ�����仯ʱ���á��ڶ�������ָʾ�仯���������ͣ�������@code ECharacterStatusType::PropertyEnd \endcode��
     * ��˵���ж�����Է����˱仯��
     */
    DECLARE_EVENT_TwoParams(ICharacterStatusProperty, FOnPropertyChangedEvent, const ICharacterStatusProperty&, ECharacterStatusType)

    using FStatusTransformer = ValueTransformer<void*, ECharacterStatusType, int32, int32>;
    typedef std::function<int32(void*, ECharacterStatusType, int32)> FTransformAction;

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
    ICharacterStatusProperty() = default;
    ICharacterStatusProperty(const ICharacterStatusProperty&) = default;
    ICharacterStatusProperty(ICharacterStatusProperty&&) = default;

    virtual ~ICharacterStatusProperty() = default;

    ICharacterStatusProperty& operator=(const ICharacterStatusProperty&) = default;
    ICharacterStatusProperty& operator=(ICharacterStatusProperty&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() const { return OnPropertyChangedEvent; }

    virtual int32 GetPropertyValue(ECharacterStatusType type) const = 0;
    virtual const FCharacterStatusInfo& GetAccumulatedInfo() const = 0;

    virtual void UpdatePropertyValue(ECharacterStatusType type) = 0;
    virtual void UpdateAllProperties() = 0;

    void AddTransformer(void* key, ECharacterStatusType type, const FTransformAction& func)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.AddTransformer(key, type, func);
        UpdatePropertyValue(type);
    }

    void RemoveTransformer(void* key, ECharacterStatusType type)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.RemoveTransformer(key, type);
        UpdatePropertyValue(type);
    }

protected:
    FStatusTransformer Transformer;
};
