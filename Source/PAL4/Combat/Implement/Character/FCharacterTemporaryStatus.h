#pragma once

#include <Platform.h>

#include "Primitives/Model/FCharacterCombatStatus.h"
#include "CombatDelegate/Character/ICharacterTempStatus.h"


/**
 * 用于存储临时的状态信息，比如战斗中使用技能、仙术等附加的Buff
 */
class PAL4_API FCharacterTemporaryStatus : public ICharacterTempStatus
{
public:
    explicit FCharacterTemporaryStatus(const ICharacterStatusProperty&);
    FCharacterTemporaryStatus(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus(FCharacterTemporaryStatus&&) noexcept;

    ~FCharacterTemporaryStatus();

    FCharacterTemporaryStatus& operator=(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus& operator=(FCharacterTemporaryStatus&&) = default;


    int32 GetPropertyValue(ECharacterStatusType type) const override;
    const FCharacterStatusInfo& GetAccumulatedInfo() const override { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) override;
    void UpdateAllProperties() override;

    const FCombatStatus& GetBattleStatus() const override { return BattleStatus; }

private:
    void OnCombatStatusChanged(ECombatStatus) const;
    void OnPersistentStatusChanged(const ICharacterStatusProperty&, ECharacterStatusType);

public:
    void SetCommonBuffStatus(ECommonBuff value) override
    {
        BattleStatus.CommonBuff = value;
        OnCombatStatusChanged(ECombatStatus::CommonBuff);
    }

    void SetPoisonStatus(EPoison value) override
    {
        BattleStatus.Poison = value;
        OnCombatStatusChanged(ECombatStatus::Poison);
    }

    void SetControlledDebuffStatus(EControlledDebuff value) override
    {
        BattleStatus.ControlledDebuff = value;
        OnCombatStatusChanged(ECombatStatus::ControlledDebuff);
    }

    void SetInVisibleStatus(bool value) override
    {
        BattleStatus.IsInvisible = value;
        OnCombatStatusChanged(ECombatStatus::Invisible);
    }

    void SetReviveStatus(bool value) override
    {
        BattleStatus.CanRevive = value;
        OnCombatStatusChanged(ECombatStatus::CanRevive);
    }

private:
    const ICharacterStatusProperty& PersistentStatus;
    FCharacterStatusInfo InfoModel;
    FCombatStatus BattleStatus;
};
