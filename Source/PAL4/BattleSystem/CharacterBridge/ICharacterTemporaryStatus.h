#pragma once

#include <Delegate.h>

#include "CharacterPrimitives/Model/ECharacterStatusType.h"
#include "CharacterPrimitives/Model/FCharacterStatusInfo.h"
#include "CharacterPrimitives/Model/FCharacterBattleStatus.h"


/*
 * �ṩ����ʱ���Լ�ս��״̬��Ϣ�ķ��ʺ͹۲�
 */
class PAL4_API ICharacterTemporaryStatus
{
public:
    /**
     * ������ֵ�����仯ʱ���á��ڶ�������ָʾ�仯���������ͣ�������@code ECharacterStatusType::PropertyEnd\endcode��
     * ��˵���ж�����Է����˱仯��
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

