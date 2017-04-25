#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Core/ValueTransformer.h"

#include "Character/FCharacterPersistentStatus.h"
#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/Model/FCharacterStatusInfo.h"
#include "Primitives/Model/FCharacterBattleStatus.h"

template ValueTransformer<void*, ECharacterStatusType, int32, int32, int32>;
typedef ValueTransformer<void*, ECharacterStatusType, int32, int32, int32> FTemporaryTransformer;


/**
 * 用于存储临时的状态信息，比如战斗中使用技能、仙术等附加的Buff
 */
class PAL4_API FCharacterTemporaryStatus
{
public:
    typedef std::function<int32(void*, ECharacterStatusType, int32, int32)> FTransformAction;

    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterStatusType::PropertyEnd\endcode，
     * 则说明有多个属性发生了变化。
     */
    DECLARE_EVENT_TwoParams(FCharacterTemporaryStatus, FOnPropertyChangedEvent, const FCharacterTemporaryStatus&, ECharacterStatusType)
    DECLARE_EVENT_TwoParams(FCharacterTemporaryStatus, FOnBattleStatusChangedEvent, const FCharacterTemporaryStatus&, ECharacterBattleStatus)

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnBattleStatusChangedEvent OnBattleStatusChangedEvent;

public:
    explicit FCharacterTemporaryStatus(FCharacterPersistentStatus&);
    FCharacterTemporaryStatus(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus(FCharacterTemporaryStatus&&);

    ~FCharacterTemporaryStatus();

    FCharacterTemporaryStatus& operator=(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus& operator=(FCharacterTemporaryStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnBattleStatusChangedEvent& OnBattleStatusChanged() { return OnBattleStatusChangedEvent; }

    const FCharacterBattleStatus& GetBattleStatus() const { return BattleStatus; }

    int32 GetPropertyValue(ECharacterStatusType type) const { return TemporaryInfoAccessor.GetPropertyValue(type); }
    const FCharacterStatusInfo& GetAccumulatedInfo() const { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) const;
    void UpdateAllProperties() const;

    void AddTransformer(void*, ECharacterStatusType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterStatusType type);

private:
    void NotifyBattleStatusChanged(ECharacterBattleStatus);
    void OnPersistentStatusChanged(const FCharacterPersistentStatus&, ECharacterStatusType) const;

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
    FCharacterStatusInfo InfoModel;
    FCharacterPersistentStatus& PersistentStatus;

    FCharacterBattleStatus BattleStatus;

    FStatusInfoAccessHelper BaseInfoAccessor;
    FStatusInfoAccessHelper PersistentInfoAccessor;
    FStatusInfoAccessHelper TemporaryInfoAccessor;

    FTemporaryTransformer Transformer;
};
