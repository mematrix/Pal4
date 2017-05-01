#pragma once

#include <Delegate.h>

#include "Primitives/Property/ICharacterStatusProperty.h"
#include "Primitives/EnumType/ECharacterCombatStatus.h"

struct FCharacterCombatStatus;
struct FCharacterStatusInfo;


class PAL4_API ICharacterTempStatus : public ICharacterStatusProperty
{
public:
    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型
     */
    DECLARE_EVENT_TwoParams(ICharacterTempStatus, FOnBattleStatusChangedEvent, const ICharacterTempStatus&, ECharacterCombatStatus)

private:
    mutable FOnBattleStatusChangedEvent OnBattleStatusChangedEvent;

protected:
    void NotifyCombatStatusChanged(ECharacterCombatStatus status) const
    {
        if (OnBattleStatusChangedEvent.IsBound())
        {
            OnBattleStatusChangedEvent.Broadcast(*this, status);
        }
    }

public:
    ICharacterTempStatus() = default;
    ICharacterTempStatus(const ICharacterTempStatus&) = default;
    ICharacterTempStatus(ICharacterTempStatus&&) = default;
    
    ICharacterTempStatus& operator=(const ICharacterTempStatus&) = default;
    ICharacterTempStatus& operator=(ICharacterTempStatus&&) = default;

    FOnBattleStatusChangedEvent& OnBattleStatusChanged() const { return OnBattleStatusChangedEvent; }

    /**
     * 获取状态信息（Buff、Debuff、中毒等）
     */
    virtual const FCharacterCombatStatus& GetBattleStatus() const = 0;

    virtual void SetCommonBuffStatus(ECommonBuff value) = 0;

    virtual void SetPoisonStatus(EPoison value) = 0;

    virtual void SetControlledDebuffStatus(EControlledDebuff value) = 0;

    virtual void SetInVisibleStatus(bool value) = 0;

    virtual void SetReviveStatus(bool value) = 0;
};
