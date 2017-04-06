// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Core/ValueTransformer.h"
#include "Helper/FStatusInfoAccessHelper.h"
#include "Model/ECharacterStatusPropertyType.h"
#include "Model/FCharacterStatusInfo.h"

template ValueTransformer<void*, ECharacterStatusPropertyType, int32, int32>;
typedef ValueTransformer<void*, ECharacterStatusPropertyType, int32, int32> FPersistentTransformer;


/**
 * ���ڴ洢�־û���״̬��Ϣ������װ�����������ܴ�����״̬��Ϣ
 */
class PAL4_API FCharacterPersistentStatus
{
public:
    typedef std::function<int32(void*, ECharacterStatusPropertyType, int32)> FTransformAction;

    /**
     * ������ֵ�����仯ʱ���á��ڶ�������ָʾ�仯���������ͣ�������@code ECharacterStatusPropertyType::PropertyEnd \endcode��
     * ��˵���ж�����Է����˱仯��
     */
    DECLARE_EVENT_TwoParams(FCharacterPersistentStatus, FOnPropertyChangedEvent, const FCharacterPersistentStatus&, ECharacterStatusPropertyType)

public:
    explicit FCharacterPersistentStatus(FStatusInfoAccessHelper& base);
    FCharacterPersistentStatus(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus(FCharacterPersistentStatus&&) = default;

    FCharacterPersistentStatus& operator=(const FCharacterPersistentStatus&) = delete;
    FCharacterPersistentStatus& operator=(FCharacterPersistentStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }

    int32 GetPropertyValue(ECharacterStatusPropertyType type) const { return PersistentInfoAccessor.GetPropertyValue(type); }
    const FCharacterStatusInfo& GetAccumulateInfo() const { return InfoModel; }

    void UpdatePropertyValue(ECharacterStatusPropertyType type) const;
    void UpdateAllProperties() const;

    void AddTransformer(void*, ECharacterStatusPropertyType, const FTransformAction&);

    void RemoveTransformer(void* key, ECharacterStatusPropertyType type);

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;

    FCharacterStatusInfo InfoModel;

    FStatusInfoAccessHelper BaseInfoAccessor;
    FStatusInfoAccessHelper PersistentInfoAccessor;

    FPersistentTransformer Transformer;
};
