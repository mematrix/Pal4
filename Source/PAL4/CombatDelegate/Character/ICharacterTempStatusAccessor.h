#pragma once

#include <Delegate.h>

#include "Util/MacroUtil.h"
#include "CharacterPrimitives/Model/ECharacterStatusType.h"
#include "CharacterPrimitives/Model/ECharacterBattleStatus.h"

struct FCharacterBattleStatus;
struct FCharacterStatusInfo;


class PAL4_API ICharacterTempStatusAccessor
{
public:
    /**
     * ������ֵ�����仯ʱ���á��ڶ�������ָʾ�仯���������ͣ�������@code ECharacterStatusType::PropertyEnd\endcode��
     * ��˵���ж�����Է����˱仯��
     */
    DECLARE_EVENT_TwoParams(ICharacterTempStatusAccessor, FOnPropertyChangedEvent, const ICharacterTempStatusAccessor&, ECharacterStatusType)
    DECLARE_EVENT_TwoParams(ICharacterTempStatusAccessor, FOnBattleStatusChangedEvent, const ICharacterTempStatusAccessor&, ECharacterBattleStatus)

protected:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnBattleStatusChangedEvent OnBattleStatusChangedEvent;

public:
    ICharacterTempStatusAccessor() : OnPropertyChangedEvent(), OnBattleStatusChangedEvent()
    {
    }

    MAKE_DEFAULT_COPY_MOVE_CTOR_AND_OP(ICharacterTempStatusAccessor)

    virtual ~ICharacterTempStatusAccessor()
    {
    }

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnBattleStatusChangedEvent& OnBattleStatusChanged() { return OnBattleStatusChangedEvent; }

    /**
     * ��ȡ״̬��Ϣ��Buff��Debuff���ж��ȣ�
     */
    virtual const FCharacterBattleStatus& GetBattleStatus() const = 0;

    /**
     * ����ָ�����������Ͳ�ѯ��Ӧ����ֵ�������������ٷ�������
     * @param type Ҫ��ѯ����������
     */
    virtual int32 GetPropertyValue(ECharacterStatusType type) const = 0;

    /**
     * ��ȡ����������������Ϣ
     */
    virtual const FCharacterStatusInfo& GetAccumulatedInfo() const = 0;
};
