#pragma once

#include <Delegate.h>

#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/Model/FCharacterStatusInfo.h"


class PAL4_API ICharacterStatusProperty
{
public:
    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterStatusType::PropertyEnd \endcode，
     * 则说明有多个属性发生了变化。
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
