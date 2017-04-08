#pragma once

#include <Delegate.h>

#include "CharacterPrimitives/Model/ECharacterStatusType.h"
#include "CharacterPrimitives/Model/FCharacterStatusInfo.h"
#include "CharacterPrimitives/Model/FCharacterBattleStatus.h"


/*
 * 提供对临时属性及战斗状态信息的访问和观察
 */
class PAL4_API ICharacterTemporaryStatus
{
public:
    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterStatusType::PropertyEnd\endcode，
     * 则说明有多个属性发生了变化。
     */
    DECLARE_EVENT_TwoParams(ICharacterTemporaryStatus, FOnPropertyChangedEvent, const ICharacterTemporaryStatus&, ECharacterStatusType)
    DECLARE_EVENT_TwoParams(ICharacterTemporaryStatus, FOnBattleStatusChangedEvent, const ICharacterTemporaryStatus&, ECharacterBattleStatus)

public:
    ICharacterTemporaryStatus() = default;
    ICharacterTemporaryStatus(const ICharacterTemporaryStatus&) = default;
    ICharacterTemporaryStatus(ICharacterTemporaryStatus&&) = default;

    virtual ~ICharacterTemporaryStatus() = default;

    ICharacterTemporaryStatus& operator=(const ICharacterTemporaryStatus&) = default;
    ICharacterTemporaryStatus& operator=(ICharacterTemporaryStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnBattleStatusChangedEvent& OnBattleStatusChanged() { return OnBattleStatusChangedEvent; }

    const FCharacterBattleStatus& GetBattleStatus() const { return BattleStatus; }

    virtual int32 GetPropertyValue(ECharacterStatusType type) const = 0;
    virtual const FCharacterStatusInfo& GetAccumulatedInfo() const = 0;

protected:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnBattleStatusChangedEvent OnBattleStatusChangedEvent;

    FCharacterBattleStatus BattleStatus;
};

