#pragma once

#include "Combat/Interface/Character/ITemporaryStatus.h"


/**
 * 用于存储临时的状态信息，比如战斗中使用技能、仙术等附加的Buff
 */
class PAL4_API FTemporaryStatus : public ITemporaryStatus
{
public:
    explicit FTemporaryStatus(const ICharacterStatus&);
    FTemporaryStatus(const FTemporaryStatus&) = delete;
    FTemporaryStatus(FTemporaryStatus&&) noexcept;

    ~FTemporaryStatus();

    FTemporaryStatus& operator=(const FTemporaryStatus&) = delete;
    FTemporaryStatus& operator=(FTemporaryStatus&&) = default;


    int32 GetPropertyValue(ECharacterStatusType type) const override;
    const FCharacterStatusInfo& GetAccumulatedInfo() const override { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusType type) override;
    void UpdateAllProperties() override;

private:
    void OnCombatStatusChanged(ECombatStatus) const;
    void OnPersistentStatusChanged(const ICharacterStatus&, ECharacterStatusType);

public:
    void SetBuffStatus(EBuff value) override
    {
        Buff = value;
        OnCombatStatusChanged(ECombatStatus::Buff);
    }

    void SetPoisonStatus(EPoison value) override
    {
        Poison = value;
        OnCombatStatusChanged(ECombatStatus::Poison);
    }

    void SetDebuffStatus(EDebuff value) override
    {
        Debuff = value;
        OnCombatStatusChanged(ECombatStatus::Debuff);
    }

    void SetInvisibleStatus(bool value) override
    {
        Invisible = value;
        OnCombatStatusChanged(ECombatStatus::Invisible);
    }

    void SetResurrectStatus(bool value) override
    {
        Resurrect = value;
        OnCombatStatusChanged(ECombatStatus::Resurrect);
    }

    EBuff GetBuffStatus() const override
    {
        return Buff;
    }

    EPoison GetPoisonStatus() const override
    {
        return Poison;
    }

    EDebuff GetDebuffStatus() const override
    {
        return Debuff;
    }

    bool IsInvisible() const override
    {
        return Invisible;
    }

    bool CanResurrect() const override
    {
        return Resurrect;
    }

private:
    const ICharacterStatus& PersistentStatus;
    FCharacterStatusInfo InfoModel;

    // 通用Buff：镜壁界宁
    EBuff Buff;
    // 中毒状态
    EPoison Poison;
    // 控制性Debuff
    EDebuff Debuff;
    // 是否隐身状态
    bool Invisible;
    // 是否可在死亡后立即复活。“生”状态
    bool Resurrect;
};
