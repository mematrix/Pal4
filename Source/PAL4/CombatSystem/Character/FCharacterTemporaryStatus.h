#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Primitives/Model/FCharacterBattleStatus.h"
#include "Primitives/Property/ICharacterStatusProperty.h"


/**
 * 用于存储临时的状态信息，比如战斗中使用技能、仙术等附加的Buff
 */
class PAL4_API FCharacterTemporaryStatus : ICharacterStatusProperty
{
public:
    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterStatusType::PropertyEnd\endcode，
     * 则说明有多个属性发生了变化。
     */
    DECLARE_EVENT_TwoParams(FCharacterTemporaryStatus, FOnBattleStatusChangedEvent, const FCharacterTemporaryStatus&, ECharacterBattleStatus)

private:
    mutable FOnBattleStatusChangedEvent OnBattleStatusChangedEvent;

public:
    explicit FCharacterTemporaryStatus(const ICharacterStatusProperty&);
    FCharacterTemporaryStatus(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus(FCharacterTemporaryStatus&&) noexcept;

    ~FCharacterTemporaryStatus();

    FCharacterTemporaryStatus& operator=(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus& operator=(FCharacterTemporaryStatus&&) = default;

    FOnBattleStatusChangedEvent& OnBattleStatusChanged() const { return OnBattleStatusChangedEvent; }

    int32 GetPropertyValue(ECharacterStatusType type) const override;
    const FCharacterStatusInfo& GetAccumulatedInfo() const override { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) override;
    void UpdateAllProperties() override;

    const FCharacterBattleStatus& GetBattleStatus() const { return BattleStatus; }

private:
    void NotifyBattleStatusChanged(ECharacterBattleStatus);
    void OnPersistentStatusChanged(const ICharacterStatusProperty&, ECharacterStatusType);

public:
    void SetCommonBuffStatus(ECommonBuff value)
    {
        BattleStatus.CommonBuff = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::CommonBuff);
    }

    void SetPoisonStatus(EPoison value)
    {
        BattleStatus.Poison = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::Poison);
    }

    void SetControlledDebuffStatus(EControlledDebuff value)
    {
        BattleStatus.ControlledDebuff = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::ControlledDebuff);
    }

    void SetInVisibleStatus(bool value)
    {
        BattleStatus.IsInvisible = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::Invisible);
    }

    void SetReviveStatus(bool value)
    {
        BattleStatus.CanRevive = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::CanRevive);
    }

private:
    const ICharacterStatusProperty& PersistentStatus;
    FCharacterStatusInfo InfoModel;
    FCharacterBattleStatus BattleStatus;
};
