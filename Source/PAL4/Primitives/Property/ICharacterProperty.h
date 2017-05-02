#pragma once

#include <Delegate.h>

#include "../EnumType/EImmune.h"
#include "../EnumType/ECharacterBasicType.h"
#include "../Model/FCharacterBasicInfo.h"

struct FCharacterInherentInfo;
class ICharacterStatusProperty;


class PAL4_API ICharacterProperty
{
public:
    DECLARE_EVENT_TwoParams(ICharacterProperty, FOnBasicInfoChangedEvent, const ICharacterProperty&, ECharacterBasicType)

protected:
    ICharacterProperty();

    ICharacterProperty(const ICharacterProperty&) = default;
    ICharacterProperty(ICharacterProperty&&) = default;

    ICharacterProperty& operator=(const ICharacterProperty&) = default;
    ICharacterProperty& operator=(ICharacterProperty&&) = default;

public:
    virtual ~ICharacterProperty() = default;

    FOnBasicInfoChangedEvent& OnBasicInfoChanged() const { return OnBasicInfoChangedEvent; }

    virtual bool IsDebuffImmune(EImmune) const = 0;

    virtual const FCharacterInherentInfo& GetCharacterInherentInfo() const = 0;

    virtual ICharacterStatusProperty& StatusProperty() = 0;
    virtual const ICharacterStatusProperty& StatusProperty() const = 0;

    const FCharacterBasicInfo& GetBasicInfo() const { return BasicInfo; }
    int32 GetBasicInfo(ECharacterBasicType) const;
    void SetBasicInfo(ECharacterBasicType, int32);

private:
    mutable FOnBasicInfoChangedEvent OnBasicInfoChangedEvent;
    FCharacterBasicInfo BasicInfo;
};
