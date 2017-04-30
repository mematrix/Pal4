#pragma once

#include <Platform.h>

#include "Primitives/Model/FCharacterBattleStatus.h"
#include "CombatDelegate/Character/ICharacterTempStatus.h"


/**
 * ���ڴ洢��ʱ��״̬��Ϣ������ս����ʹ�ü��ܡ������ȸ��ӵ�Buff
 */
class PAL4_API FCharacterTemporaryStatus : public ICharacterTempStatus
{
public:
    explicit FCharacterTemporaryStatus(const ICharacterStatusProperty&);
    FCharacterTemporaryStatus(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus(FCharacterTemporaryStatus&&) noexcept;

    ~FCharacterTemporaryStatus();

    FCharacterTemporaryStatus& operator=(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus& operator=(FCharacterTemporaryStatus&&) = default;


    int32 GetPropertyValue(ECharacterStatusType type) const override;
    const FCharacterStatusInfo& GetAccumulatedInfo() const override { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) override;
    void UpdateAllProperties() override;

    const FCharacterBattleStatus& GetBattleStatus() const override { return BattleStatus; }

private:
    void OnCombatStatusChanged(ECharacterBattleStatus) const;
    void OnPersistentStatusChanged(const ICharacterStatusProperty&, ECharacterStatusType);

public:
    void SetCommonBuffStatus(ECommonBuff value) override
    {
        BattleStatus.CommonBuff = value;
        OnCombatStatusChanged(ECharacterBattleStatus::CommonBuff);
    }

    void SetPoisonStatus(EPoison value) override
    {
        BattleStatus.Poison = value;
        OnCombatStatusChanged(ECharacterBattleStatus::Poison);
    }

    void SetControlledDebuffStatus(EControlledDebuff value) override
    {
        BattleStatus.ControlledDebuff = value;
        OnCombatStatusChanged(ECharacterBattleStatus::ControlledDebuff);
    }

    void SetInVisibleStatus(bool value) override
    {
        BattleStatus.IsInvisible = value;
        OnCombatStatusChanged(ECharacterBattleStatus::Invisible);
    }

    void SetReviveStatus(bool value) override
    {
        BattleStatus.CanRevive = value;
        OnCombatStatusChanged(ECharacterBattleStatus::CanRevive);
    }

private:
    const ICharacterStatusProperty& PersistentStatus;
    FCharacterStatusInfo InfoModel;
    FCharacterBattleStatus BattleStatus;
};
