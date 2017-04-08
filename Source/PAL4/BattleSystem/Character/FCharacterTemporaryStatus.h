#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Core/ValueTransformer.h"
//#include "Util/TypeTraitsUtil.h"

#include "CharacterPrimitives/Helper/FStatusInfoAccessHelper.h"
#include "CharacterPrimitives/Model/ECharacterStatusType.h"
#include "CharacterPrimitives/Model/FCharacterStatusInfo.h"
#include "CharacterPrimitives/Model/ECharacterBattleStatus.h"
#include "CharacterPrimitives/FCharacterPersistentStatus.h"

template ValueTransformer<void*, ECharacterStatusType, int32, int32, int32>;
typedef ValueTransformer<void*, ECharacterStatusType, int32, int32, int32> FTemporaryTransformer;

//template<ECharacterBattleStatus v1, ECharacterBattleStatus v2>
//using is_status_equal = pal4::is_equal<ECharacterBattleStatus, v1, v2>;


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

public:
    explicit FCharacterTemporaryStatus(FCharacterPersistentStatus&);
    FCharacterTemporaryStatus(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus(FCharacterTemporaryStatus&&) = default;

    ~FCharacterTemporaryStatus();

    FCharacterTemporaryStatus& operator=(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus& operator=(FCharacterTemporaryStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnBattleStatusChangedEvent& OnBattleStatusChanged() { return OnBattleStatusChangedEvent; }

    int32 GetPropertyValue(ECharacterStatusType type) const { return TemporaryInfoAccessor.GetPropertyValue(type); }
    const FCharacterStatusInfo& GetAccumulatedInfo() const { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) const;
    void UpdateAllProperties() const;

    void AddTransformer(void*, ECharacterStatusType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterStatusType type);

    ECommonBuff GetCommonBuffStatus() const { return CommonBuff; }
    EPoison GetPoisonStatus() const { return Poison; }
    EControlledDebuff GetControlledDebuffStatus() const { return ControlledDebuff; }
    bool GetInVisibleStatus() const { return IsInvisible; }
    bool GetReviveStatus() const { return CanRevive; }

    void SetCommonBuffStatus(ECommonBuff value)
    {
        CommonBuff = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::CommonBuff);
    }

    void SetPoisonStatus(EPoison value)
    {
        Poison = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::Poison);
    }

    void SetControlledDebuffStatus(EControlledDebuff value)
    {
        ControlledDebuff = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::ControlledDebuff);
    }

    void SetInVisibleStatus(bool value)
    {
        IsInvisible = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::Invisible);
    }

    void SetReviveStatus(bool value)
    {
        CanRevive = value;
        NotifyBattleStatusChanged(ECharacterBattleStatus::CanRevive);
    }

private:
    void NotifyBattleStatusChanged(ECharacterBattleStatus);
    void OnPersistentStatusChanged(const FCharacterPersistentStatus&, ECharacterStatusType) const;

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnBattleStatusChangedEvent OnBattleStatusChangedEvent;

    FCharacterStatusInfo InfoModel;
    FCharacterPersistentStatus& PersistentStatus;

    FStatusInfoAccessHelper BaseInfoAccessor;
    FStatusInfoAccessHelper PersistentInfoAccessor;
    FStatusInfoAccessHelper TemporaryInfoAccessor;

    FTemporaryTransformer Transformer;

    // Buff状态
    // 通用Buff：镜壁界宁
    ECommonBuff CommonBuff;
    // 中毒状态
    EPoison Poison;
    // 控制性Debuff
    EControlledDebuff ControlledDebuff;
    // 是否隐身状态
    bool IsInvisible;
    // 是否可在死亡后立即复活。“生”状态
    bool CanRevive;
};
