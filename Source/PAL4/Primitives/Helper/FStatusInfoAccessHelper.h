#pragma once

#include <Platform.h>

#include "../EnumType/ECharacterStatusType.h"

struct FCharacterStatusInfo;


extern int32 FCharacterStatusInfo::* const PropertySet[PropertySetCount];

constexpr int32 FCharacterStatusInfo::* GetPropertyPtr(ECharacterStatusType type)
{
    return PropertySet[static_cast<int32>(type)];
}


class PAL4_API FStatusInfoAccessHelper
{
public:
    FStatusInfoAccessHelper(FCharacterStatusInfo& model) : InfoModel(model) { }

    explicit operator FCharacterStatusInfo&() const { return InfoModel; }
    FCharacterStatusInfo& GetModel() const { return InfoModel; }

    inline int32 GetPropertyValue(ECharacterStatusType type) const;
    inline void SetPropertyValue(ECharacterStatusType type, int32 value) const;
    
    inline void AddPropertyValue(ECharacterStatusType type, int32 value) const;

    template<ECharacterStatusType Type>
    int32 GetPropertyValue() const
    {
        static_assert(static_cast<uint32>(Type) < PropertySetCount, 
            "value of generic type argument must be less than countof(ECharacterProperty)");
        return InfoModel.*GetPropertyPtr(Type);
    }

private:
    FCharacterStatusInfo& InfoModel;
};

class PAL4_API FStatusInfoReader
{
public:
    FStatusInfoReader(const FCharacterStatusInfo& model) : InfoModel(model) { }

    explicit operator const FCharacterStatusInfo&() const { return InfoModel; }
    const FCharacterStatusInfo& GetModel() const { return InfoModel; }

    inline int32 GetPropertyValue(ECharacterStatusType type) const;

    template<ECharacterStatusType Type>
    int32 GetPropertyValue() const
    {
        static_assert(static_cast<uint32>(Type) < PropertySetCount,
            "value of generic type argument must be less than countof(ECharacterProperty)");
        return InfoModel.*GetPropertyPtr(Type);
    }

private:
    const FCharacterStatusInfo& InfoModel;
};
