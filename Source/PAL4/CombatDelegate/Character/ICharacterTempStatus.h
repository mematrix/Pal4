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
     * ������ֵ�����仯ʱ���á��ڶ�������ָʾ�仯����������
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
     * ��ȡ״̬��Ϣ��Buff��Debuff���ж��ȣ�
     */
    virtual const FCharacterCombatStatus& GetBattleStatus() const = 0;

    virtual void SetCommonBuffStatus(ECommonBuff value) = 0;

    virtual void SetPoisonStatus(EPoison value) = 0;

    virtual void SetControlledDebuffStatus(EControlledDebuff value) = 0;

    virtual void SetInVisibleStatus(bool value) = 0;

    virtual void SetReviveStatus(bool value) = 0;
};
