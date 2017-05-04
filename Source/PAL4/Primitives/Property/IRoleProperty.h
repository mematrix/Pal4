#pragma once

#include "ICharacterProperty.h"
#include "../EnumType/ERole.h"


class PAL4_API IRoleProperty : public ICharacterProperty
{
public:
    bool IsDebuffImmune(EImmune) const override final { return false; }

    virtual void SetRoleFavor(ERole, int32) = 0;

    virtual void AddRoleFavor(ERole, int32) = 0;

    virtual int32 GetRoleFavor(ERole) const = 0;
};
