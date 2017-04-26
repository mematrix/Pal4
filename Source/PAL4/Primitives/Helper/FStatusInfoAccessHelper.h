#pragma once

#include <Platform.h>

#include "../EnumType/ECharacterStatusType.h"

struct FCharacterStatusInfo;


class PAL4_API FStatusInfoAccessHelper
{
public:
    FStatusInfoAccessHelper(FCharacterStatusInfo& model) : InfoModel(model) { }

    explicit operator FCharacterStatusInfo&() const { return InfoModel; }
    FCharacterStatusInfo& GetModel() const { return InfoModel; }

    int32 GetPropertyValue(ECharacterStatusType type) const;
    void SetPropertyValue(ECharacterStatusType type, int32 value) const;
    
    void AddPropertyValue(ECharacterStatusType type, int32 value) const;

    template<ECharacterStatusType Type>
    int32 GetPropertyValue() const
    {
        static_assert(GetLowBitIndex(Type) < PropertySetCount, 
            "Shift count of generic type argument value must be less than countof(ECharacterProperty)");
        return InfoModel.*GetPropertyPtr(Type);
    }

private:
    FCharacterStatusInfo& InfoModel;

public:
    constexpr static int32 FCharacterStatusInfo::* GetPropertyPtr(ECharacterStatusType type)
    {
        return PropertySet[static_cast<int32>(type)];
    }

    static int32 FCharacterStatusInfo::* const PropertySet[PropertySetCount];
};
