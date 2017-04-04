#pragma once

#include <Platform.h>

#include "../Model/ECharacterPropertyType.h"

class FCharacterInfoModel;

class PAL4_API FInfoModelAccessHelper
{
public:
    FInfoModelAccessHelper(FCharacterInfoModel& model) : InfoModel(model) { }

    explicit operator FCharacterInfoModel&() const { return InfoModel; }
    FCharacterInfoModel& GetModel() const { return InfoModel; }

    int32 GetPropertyValue(ECharacterPropertyType type) const;
    void SetPropertyValue(ECharacterPropertyType type, int32 value) const;

    template<ECharacterPropertyType Type>
    int32 GetPropertyValue() const
    {
        static_assert(static_cast<uint32>(Type) < PropertySetCount, 
            "Value of generic type argument must be less than (uint32)ECharacterProperty::PropertyEnd");
        return InfoModel.*GetPropertyPtr(Type);
    }

private:
    FCharacterInfoModel& InfoModel;

public:
    constexpr static int32 FCharacterInfoModel::* GetPropertyPtr(ECharacterPropertyType type)
    {
        return PropertySet[static_cast<int32>(type)];
    }

    static int32 FCharacterInfoModel::* const PropertySet[PropertySetCount];
};
