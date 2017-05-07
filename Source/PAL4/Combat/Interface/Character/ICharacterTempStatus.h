#pragma once

#include <Delegate.h>

#include "Primitives/Property/ICharacterStatusProperty.h"
#include "Primitives/EnumType/ECombatStatus.h"

struct FCombatStatus;
struct FCharacterStatusInfo;


class PAL4_API ICharacterTempStatus : public ICharacterStatusProperty
{
public:
    /**
     * ������ֵ�����仯ʱ���á��ڶ�������ָʾ�仯����������
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
     * ��ȡ״̬��Ϣ��Buff��Debuff���ж��ȣ�
     */
    virtual const FCombatStatus& GetBattleStatus() const = 0;

    virtual void SetCommonBuffStatus(ECommonBuff value) = 0;

    virtual void SetPoisonStatus(EPoison value) = 0;

    virtual void SetControlledDebuffStatus(EControlledDebuff value) = 0;

    virtual void SetInVisibleStatus(bool value) = 0;

    virtual void SetReviveStatus(bool value) = 0;
};
