#pragma once

#include <Delegate.h>

#include "Primitives/EnumType/ECombatStatus.h"
#include "Character/ICharacterStatus.h"


class PAL4_API ITemporaryStatus : public ICharacterStatus
{
public:
    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型
     */
    DECLARE_EVENT_TwoParams(ITemporaryStatus, FOnCombatStatusChangedEvent, const ITemporaryStatus&, ECombatStatus)

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
    ITemporaryStatus() = default;
    ITemporaryStatus(const ITemporaryStatus&) = default;
    ITemporaryStatus(ITemporaryStatus&&) = default;
    
    ITemporaryStatus& operator=(const ITemporaryStatus&) = default;
    ITemporaryStatus& operator=(ITemporaryStatus&&) = default;

    FOnCombatStatusChangedEvent& OnBattleStatusChanged() const { return OnBattleStatusChangedEvent; }

    virtual EBuff GetBuffStatus() const = 0;

    virtual EPoison GetPoisonStatus() const = 0;

    virtual EDebuff GetDebuffStatus() const = 0;

    virtual bool IsInvisible() const = 0;

    virtual bool CanResurrect() const = 0;

    virtual void SetBuffStatus(EBuff value) = 0;

    virtual void SetPoisonStatus(EPoison value) = 0;

    virtual void SetDebuffStatus(EDebuff value) = 0;

    virtual void SetInvisibleStatus(bool value) = 0;

    virtual void SetResurrectStatus(bool value) = 0;
};
