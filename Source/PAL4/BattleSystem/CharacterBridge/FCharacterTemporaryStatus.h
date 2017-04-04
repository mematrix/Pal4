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

    // TODO: ���ͳһ�ķ���int32��ȡ״ֵ̬�������������״ֵ̬���������״̬�仯֪ͨ�¼���

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;

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
