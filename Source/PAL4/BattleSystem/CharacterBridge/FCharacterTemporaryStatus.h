#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Core/ValueTransformer.h"
//#include "Util/TypeTraitsUtil.h"

#include "Character/Helper/FInfoModelAccessHelper.h"
#include "Character/Model/ECharacterPropertyType.h"
#include "Character/Model/FCharacterInfoModel.h"
#include "ECharacterBattleStatus.h"

template ValueTransformer<void*, ECharacterPropertyType, int32, int32, int32>;
typedef ValueTransformer<void*, ECharacterPropertyType, int32, int32, int32> FTemporaryTransformer;

//template<ECharacterBattleStatus v1, ECharacterBattleStatus v2>
//using is_status_equal = pal4::is_equal<ECharacterBattleStatus, v1, v2>;


/**
 * ���ڴ洢��ʱ��״̬��Ϣ������ս����ʹ�ü��ܡ������ȸ��ӵ�Buff
 */
class PAL4_API FCharacterTemporaryStatus
{
public:
    typedef std::function<int32(void*, ECharacterPropertyType, int32, int32)> FTransformAction;

    /**
     * ������ֵ�����仯ʱ���á��ڶ�������ָʾ�仯���������ͣ�������@code ECharacterPropertyType::PropertyEnd\endcode��
     * ��˵���ж�����Է����˱仯��
     */
    DECLARE_EVENT_TwoParams(FCharacterTemporaryStatus, FOnPropertyChangedEvent, const FCharacterTemporaryStatus&, ECharacterPropertyType)
    DECLARE_EVENT_TwoParams(FCharacterTemporaryStatus, FOnBattleStatusChangedEvent, const FCharacterTemporaryStatus&, ECharacterBattleStatus)

public:
    FCharacterTemporaryStatus(const FInfoModelAccessHelper& base, const FInfoModelAccessHelper& pers);
    FCharacterTemporaryStatus(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus(FCharacterTemporaryStatus&&) = default;

    FCharacterTemporaryStatus& operator=(const FCharacterTemporaryStatus&) = delete;
    FCharacterTemporaryStatus& operator=(FCharacterTemporaryStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnBattleStatusChangedEvent& OnBattleStatusChanged() { return OnBattleStatusChangedEvent; }

    int32 GetPropertyValue(ECharacterPropertyType type) const { return TemporaryInfoAccessor.GetPropertyValue(type); }
    const FCharacterInfoModel& GetAccumulatedInfo() const { return InfoModel; }

    void UpdatePropertyValue(ECharacterPropertyType type) const;
    void UpdateAllProperties() const;

    void AddTransformer(void*, ECharacterPropertyType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterPropertyType type);

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

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnBattleStatusChangedEvent OnBattleStatusChangedEvent;

    FCharacterInfoModel InfoModel;

    FInfoModelAccessHelper BaseInfoAccessor;
    FInfoModelAccessHelper PersistentInfoAccessor;
    FInfoModelAccessHelper TemporaryInfoAccessor;

    FTemporaryTransformer Transformer;

    // Buff״̬
    // ͨ��Buff�����ڽ���
    ECommonBuff CommonBuff;
    // �ж�״̬
    EPoison Poison;
    // ������Debuff
    EControlledDebuff ControlledDebuff;
    // �Ƿ�����״̬
    bool IsInvisible;
    // �Ƿ�����������������������״̬
    bool CanRevive;
};
