#pragma once

#include <Delegate.h>

#include "../EnumType/EImmune.h"
#include "../EnumType/ECharacterBasicType.h"
#include "../EnumType/ECharacterStatusType.h"
#include "../Model/FCharacterBasicInfo.h"

struct FCharacterStatusInfo;
struct FCharacterInherentInfo;
class ICharacterStatusProperty;


class PAL4_API ICharacterProperty
{
public:
    DECLARE_EVENT_TwoParams(ICharacterProperty, FOnBasicInfoChangedEvent, const ICharacterProperty&, ECharacterBasicType)
    /**
     * 当人物等级升级之后触发事件
     */
    DECLARE_EVENT_TwoParams(ICharacterProperty, FOnLevelUpgradedEvent, const ICharacterProperty&, int32)

protected:
    ICharacterProperty();

    ICharacterProperty(const ICharacterProperty&) = default;
    ICharacterProperty(ICharacterProperty&&) = default;

    ICharacterProperty& operator=(const ICharacterProperty&) = default;
    ICharacterProperty& operator=(ICharacterProperty&&) = default;

public:
    virtual ~ICharacterProperty() = default;

    FOnBasicInfoChangedEvent& OnBasicInfoChanged() const { return OnBasicInfoChangedEvent; }

    FOnLevelUpgradedEvent& OnLevenUpgraded() const { return OnLevelUpgradedEvent; }

    virtual void UpdateStatusInfo(ECharacterStatusType, int32) = 0;

    virtual void UpdateStatusInfo(const FCharacterStatusInfo&) = 0;

    virtual bool IsDebuffImmune(EImmune) const = 0;

    virtual const FCharacterInherentInfo& GetCharacterInherentInfo() const = 0;

    virtual ICharacterStatusProperty& StatusProperty() = 0;
    virtual const ICharacterStatusProperty& StatusProperty() const = 0;

    const FCharacterBasicInfo& GetBasicInfo() const { return BasicInfo; }
    int32 GetBasicInfo(ECharacterBasicType) const;
    void SetBasicInfo(ECharacterBasicType, int32);

private:
    mutable FOnBasicInfoChangedEvent OnBasicInfoChangedEvent;
    mutable FOnLevelUpgradedEvent OnLevelUpgradedEvent;
    FCharacterBasicInfo BasicInfo;
};
