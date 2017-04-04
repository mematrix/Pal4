#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Core/ValueTransformer.h"
#include "Character/Helper/FInfoModelAccessHelper.h"
#include "Character/Model/ECharacterPropertyType.h"
#include "Character/Model/FCharacterInfoModel.h"
#include "ECharacterBattleStatus.h"

template ValueTransformer<void*, ECharacterPropertyType, int32, int32, int32>;
typedef ValueTransformer<void*, ECharacterPropertyType, int32, int32, int32> FTemporaryTransformer;


/**
 * 用于存储临时的状态信息，比如战斗中使用技能、仙术等附加的Buff
 */
class PAL4_API FCharacterTemporaryStatus
{
public:
    typedef std::function<int32(void*, ECharacterPropertyType, int32, int32)> FTransformAction;

    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterPropertyType::PropertyEnd\endcode，
     * 则说明有多个属性发生了变化。
     */
    DECLARE_EVENT_TwoParams(FCharacterTemporaryStatus, FOnPropertyChangedEvent, const FCharacterTemporaryStatus&, ECharacterPropertyType)

public:
    FCharacterTemporaryStatus(const FInfoModelAccessHelper& base, const FInfoModelAccessHelper& pers);
    FCharacterTemporaryStatus(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus(FCharacterTemporaryStatus&&) = default;

    FCharacterTemporaryStatus& operator=(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus& operator=(FCharacterTemporaryStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }

    int32 GetPropertyValue(ECharacterPropertyType type) const { return TemporaryInfoAccessor.GetPropertyValue(type); }
    const FCharacterInfoModel& GetAccumulatedInfo() const { return InfoModel; }

    void UpdatePropertyValue(ECharacterPropertyType type) const;
    void UpdateAllProperties() const;

    void AddTransformer(void*, ECharacterPropertyType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterPropertyType type);

    // ReSharper disable once CppFunctionIsNotImplemented
    template<ECharacterBattleStatus Status>
    void GetStatusValue() const;

    template<>
    const FCharacterInfoModel& GetStatusValue<ECharacterBattleStatus::Property>() const { return InfoModel; }
    template<>
    ECommonBuff GetStatusValue<ECharacterBattleStatus::CommonBuff>() const { return CommonBuff; }
    template<>
    EPoison GetStatusValue<ECharacterBattleStatus::Poison>() const { return Poison; }
    template<>
    EControlledDebuff GetStatusValue<ECharacterBattleStatus::ControlledDebuff>() const { return ControlledDebuff; }
    template<>
    bool GetStatusValue<ECharacterBattleStatus::Invisible>() const { return IsInvisible; }
    template<>
    bool GetStatusValue<ECharacterBattleStatus::CanRevive>() const { return CanRevive; }

    // TODO: 添加统一的返回int32的取状态值方法。添加设置状态值方法。添加状态变化通知事件。

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;

    FCharacterInfoModel InfoModel;

    FInfoModelAccessHelper BaseInfoAccessor;
    FInfoModelAccessHelper PersistentInfoAccessor;
    FInfoModelAccessHelper TemporaryInfoAccessor;

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
