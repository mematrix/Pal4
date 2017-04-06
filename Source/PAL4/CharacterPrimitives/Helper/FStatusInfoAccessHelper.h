#pragma once

#include <Platform.h>

#include "../Model/ECharacterStatusPropertyType.h"

struct FCharacterStatusInfo;

class PAL4_API FStatusInfoAccessHelper
{
public:
    FStatusInfoAccessHelper(FCharacterStatusInfo& model) : InfoModel(model) { }

    explicit operator FCharacterStatusInfo&() const { return InfoModel; }
    FCharacterStatusInfo& GetModel() const { return InfoModel; }

    int32 GetPropertyValue(ECharacterStatusPropertyType type) const;
    void SetPropertyValue(ECharacterStatusPropertyType type, int32 value) const;
    // TODO: Ìí¼Ó+=¸³ÖµÂß¼­

    template<ECharacterStatusPropertyType Type>
    int32 GetPropertyValue() const
    {
        static_assert(static_cast<uint32>(Type) < PropertySetCount, 
            "Value of generic type argument must be less than (uint32)ECharacterProperty::PropertyEnd");
        return InfoModel.*GetPropertyPtr(Type);
    }

private:
    FCharacterStatusInfo& InfoModel;

public:
    constexpr static int32 FCharacterStatusInfo::* GetPropertyPtr(ECharacterStatusPropertyType type)
    {
        return PropertySet[static_cast<int32>(type)];
    }

    static int32 FCharacterStatusInfo::* const PropertySet[PropertySetCount];
};
