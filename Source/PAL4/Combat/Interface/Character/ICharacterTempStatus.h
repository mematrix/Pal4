#pragma once

#include <Delegate.h>

#include "Primitives/EnumType/ECombatStatus.h"
#include "Character/ICharacterStatusProperty.h"

struct FCombatStatus;
struct FCharacterStatusInfo;


class PAL4_API ICharacterTempStatus : public ICharacterStatusProperty
{
public:
    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型
     */
    DECLARE_EVENT_TwoParams(ICharacterTempStatus, FOnCombatStatusChangedEvent, const ICharacterTempStatus&, ECombatStatus)

private:
    mutable FOnCombatStatusChangedEvent OnBattleStatusChangedEvent;

protected:
    void NotifyCombatStatusChanged(ECombatStatus status) const
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

    FOnCombatStatusChangedEvent& OnBattleStatusChanged() const { return OnBattleStatusChangedEvent; }

    /**
     * 获取状态信息（Buff、Debuff、中毒等）
     */
    virtual const FCombatStatus& GetBattleStatus() const = 0;

    virtual void SetCommonBuffStatus(EBuff value) = 0;

    virtual void SetPoisonStatus(EPoison value) = 0;

    virtual void SetControlledDebuffStatus(EDebuff value) = 0;

    virtual void SetInVisibleStatus(bool value) = 0;

    virtual void SetReviveStatus(bool value) = 0;
};
