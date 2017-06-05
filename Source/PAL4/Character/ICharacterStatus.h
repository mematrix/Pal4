#pragma once

#include <Delegate.h>

#include "Core/ValueTransformer.h"
#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/Model/FCharacterStatusInfo.h"


class PAL4_API ICharacterStatus
{
public:
    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterStatusType::PropertyEnd \endcode，
     * 则说明有多个属性发生了变化。
     */
    DECLARE_EVENT_TwoParams(ICharacterStatus, FOnPropertyChangedEvent, const ICharacterStatus&, ECharacterStatusType)

    using FStatusTransformer = ValueTransformer<int32, ECharacterStatusType, int32, int32>;
    typedef std::function<int32(int32)> FTransformAction;

private:
    mutable FOnPropertyChangedEvent OnPropertyChangedEvent;

protected:
    void NotifyPropertyChanged(ECharacterStatusType type) const
    {
        if (OnPropertyChangedEvent.IsBound())
        {
            OnPropertyChangedEvent.Broadcast(*this, type);
        }
    }

public:
    ICharacterStatus() = default;
    ICharacterStatus(const ICharacterStatus&) = default;
    ICharacterStatus(ICharacterStatus&&) = default;

    virtual ~ICharacterStatus() = default;

    ICharacterStatus& operator=(const ICharacterStatus&) = default;
    ICharacterStatus& operator=(ICharacterStatus&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() const { return OnPropertyChangedEvent; }

    /**
     * 根据指定的属性类型查询对应属性值。包括武运灵速防等属性
     * @param type 要查询的属性类型
     */
    virtual int32 GetPropertyValue(ECharacterStatusType type) const = 0;

    /**
     * 获取计算后的人物属性信息
     */
    virtual const FCharacterStatusInfo& GetAccumulatedInfo() const = 0;

    /**
     * @brief 更新指定属性的值
     * @param type 需要更新值的类型
     */
    virtual void UpdatePropertyValue(ECharacterStatusType type) = 0;

    /**
     * @brief 更新全部属性的值
     */
    virtual void UpdateAllProperties() = 0;

    void AddTransformer(int32 key, ECharacterStatusType type, const FTransformAction& func)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.AddTransformer(key, type, func);
        UpdatePropertyValue(type);
    }

    void AddOrUpdateTransformer(int32 key, ECharacterStatusType type, const FTransformAction& func)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.RemoveTransformer(key, type);
        Transformer.AddTransformer(key, type, func);
        UpdatePropertyValue(type);
    }

    void RemoveTransformer(int32 key, ECharacterStatusType type)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.RemoveTransformer(key, type);
        UpdatePropertyValue(type);
    }

    void RemoveTransformerByKey(int32 key)
    {
        Transformer.RemoveKey(key);
        UpdateAllProperties();
    }

    void RemoveTransformerByStatus(ECharacterStatusType type)
    {
        _ASSERT(static_cast<uint32>(type) < PropertySetCount);

        Transformer.RemoveGroup(type);
        UpdatePropertyValue(type);
    }

protected:
    FStatusTransformer Transformer;
};
