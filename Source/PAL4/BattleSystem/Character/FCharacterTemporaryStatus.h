#pragma once

#include <Platform.h>

#include "Core/ValueTransformer.h"

#include "CharacterPrimitives/FCharacterPersistentStatus.h"
#include "../CharacterBridge/ICharacterTemporaryStatus.h"

template ValueTransformer<void*, ECharacterStatusType, int32, int32, int32>;
typedef ValueTransformer<void*, ECharacterStatusType, int32, int32, int32> FTemporaryTransformer;


/**
 * 用于存储临时的状态信息，比如战斗中使用技能、仙术等附加的Buff
 */
class PAL4_API FCharacterTemporaryStatus : public ICharacterTemporaryStatus
{
public:
    typedef std::function<int32(void*, ECharacterStatusType, int32, int32)> FTransformAction;

public:
    explicit FCharacterTemporaryStatus(FCharacterPersistentStatus&);
    FCharacterTemporaryStatus(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus(FCharacterTemporaryStatus&&);

    ~FCharacterTemporaryStatus();

    FCharacterTemporaryStatus& operator=(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus& operator=(FCharacterTemporaryStatus&&) = default;


    int32 GetPropertyValue(ECharacterStatusType type) const override { return TemporaryInfoAccessor.GetPropertyValue(type); }
    const FCharacterStatusInfo& GetAccumulatedInfo() const override { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) const;
    void UpdateAllProperties() const;

    void AddTransformer(void*, ECharacterStatusType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterStatusType type);


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
    void NotifyBattleStatusChanged(ECharacterBattleStatus);
    void OnPersistentStatusChanged(const FCharacterPersistentStatus&, ECharacterStatusType) const;

private:
    FCharacterStatusInfo InfoModel;
    FCharacterPersistentStatus& PersistentStatus;

    FStatusInfoAccessHelper BaseInfoAccessor;
    FStatusInfoAccessHelper PersistentInfoAccessor;
    FStatusInfoAccessHelper TemporaryInfoAccessor;

    FTemporaryTransformer Transformer;
};
