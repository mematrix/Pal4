#pragma once

#include <Delegate.h>

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

    ICharacterStatusProperty() = default;
    ICharacterStatusProperty(const ICharacterStatusProperty&) = default;
    ICharacterStatusProperty(ICharacterStatusProperty&&) = default;

    virtual ~ICharacterStatusProperty() = default;

    ICharacterStatusProperty& operator=(const ICharacterStatusProperty&) = default;
    ICharacterStatusProperty& operator=(ICharacterStatusProperty&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;

public:
    virtual int32 GetPropertyValue(ECharacterStatusType type) const = 0;
    virtual const FCharacterStatusInfo& GetAccumulateInfo() const = 0;

    virtual void UpdatePropertyValue(ECharacterStatusType type) const = 0;
    virtual void UpdateAllProperties() const = 0;
};
