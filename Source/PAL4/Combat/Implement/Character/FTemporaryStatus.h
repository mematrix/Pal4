#pragma once

#include "Combat/Interface/Character/ITemporaryStatus.h"


/**
 * ���ڴ洢��ʱ��״̬��Ϣ������ս����ʹ�ü��ܡ������ȸ��ӵ�Buff
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

    // ͨ��Buff�����ڽ���
    EBuff Buff;
    // �ж�״̬
    EPoison Poison;
    // ������Debuff
    EDebuff Debuff;
    // �Ƿ�����״̬
    bool Invisible;
    // �Ƿ�����������������������״̬
    bool Resurrect;
};