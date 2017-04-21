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
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterStatusType::PropertyEnd\endcode，
     * 则说明有多个属性发生了变化。
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
     * 获取状态信息（Buff、Debuff、中毒等）
     */
    virtual const FCharacterBattleStatus& GetBattleStatus() const = 0;

    /**
     * 根据指定的属性类型查询对应属性值。包括武运灵速防等属性
     * @param type 要查询的属性类型
     */
    virtual int32 GetPropertyValue(ECharacterStatusType type) const = 0;

    /**
     * 获取计算后的人物属性信息
     */
    virtual const FCharacterStatusInfo& GetAccumulatedInfo() const = 0;
};
