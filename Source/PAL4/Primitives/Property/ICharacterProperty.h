#pragma once

#include "../EnumType/EImmune.h"


class PAL4_API ICharacterProperty
{
public:
    virtual ~ICharacterProperty() = default;

    virtual bool IsDebuffImmune(EImmune) = 0;
};
