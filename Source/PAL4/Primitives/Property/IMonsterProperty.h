#pragma once

#include "ICharacterProperty.h"
#include "../Model/FMonsterImmuneInfo.h"

struct FMonsterInherentInfo;


class PAL4_API IMonsterProperty : public ICharacterProperty
{
protected:
    IMonsterProperty();
    IMonsterProperty(const IMonsterProperty&) = default;
    IMonsterProperty(IMonsterProperty&&) = default;
    
    IMonsterProperty& operator=(const IMonsterProperty&) = default;
    IMonsterProperty& operator=(IMonsterProperty&&) = default;

public:
    bool IsDebuffImmune(EImmune) const override final;

    FMonsterImmuneInfo& AttachedImmuneInfo() { return ImmuneInfo; }
    const FMonsterImmuneInfo& AttachedImmuneInfo() const { return ImmuneInfo; }

    virtual const FMonsterInherentInfo& GetMonsterInherentInfo() const = 0;

private:
    FMonsterImmuneInfo ImmuneInfo;
};
