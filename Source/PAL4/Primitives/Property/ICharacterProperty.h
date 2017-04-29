#pragma once

#include <Delegate.h>

#include "../EnumType/EImmune.h"
#include "../EnumType/ECharacterBasicType.h"
#include "../Model/FCharacterBasicInfo.h"

class ICharacterStatusProperty;


class PAL4_API ICharacterProperty
{
public:
    DECLARE_EVENT_TwoParams(ICharacterProperty, FOnBasicInfoChangedEvent, const ICharacterProperty&, ECharacterBasicType)

protected:
    ICharacterProperty(int32 id, const FName& name, ERace race, EPhysicalAttackType type, EPhysicalAttackTarget target);

    ICharacterProperty(const ICharacterProperty&) = default;
    ICharacterProperty(ICharacterProperty&&) = default;

    ICharacterProperty& operator=(const ICharacterProperty&) = default;
    ICharacterProperty& operator=(ICharacterProperty&&) = default;

public:
    virtual ~ICharacterProperty() = default;

    FOnBasicInfoChangedEvent& OnBasicInfoChanged() { return OnBasicInfoChangedEvent; }

    virtual bool IsDebuffImmune(EImmune) = 0;

    virtual ICharacterStatusProperty& GetStatusProperty() = 0;
    virtual const ICharacterStatusProperty& GetStatusProperty() const = 0;

    const FCharacterBasicInfo& GetBasicInfo() const { return BasicInfo; }
    int32 GetBasicInfo(ECharacterBasicType) const;
    void SetBasicInfo(ECharacterBasicType, int32);

protected:
    FCharacterBasicInfo BasicInfo;

private:
    FOnBasicInfoChangedEvent OnBasicInfoChangedEvent;
};
