#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "Core/ValueTransformer.h"
#include "Character/Helper/FInfoModelAccessHelper.h"
#include "Character/Model/ECharacterPropertyType.h"
#include "Character/Model/FCharacterInfoModel.h"

template ValueTransformer<void*, ECharacterPropertyType, int32, int32, int32>;
typedef ValueTransformer<void*, ECharacterPropertyType, int32, int32, int32> FTemporaryTransformer;

class PAL4_API FCharacterTemporaryStatus
{
public:
    typedef std::function<int32(void*, ECharacterPropertyType, int32, int32)> FTransformAction;

    /**
     * 当属性值发生变化时调用。第二个参数指示变化的属性类型，若等于@code ECharacterPropertyType::PropertyEnd，
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

private:
    FOnPropertyChangedEvent OnPropertyChangedEvent;

    FCharacterInfoModel InfoModel;

    FInfoModelAccessHelper BaseInfoAccessor;
    FInfoModelAccessHelper PersistentInfoAccessor;
    FInfoModelAccessHelper TemporaryInfoAccessor;

    FTemporaryTransformer Transformer;
};
