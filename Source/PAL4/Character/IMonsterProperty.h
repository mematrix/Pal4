#pragma once

#include "ICharacterProperty.h"
#include "Primitives/Model/FMonsterTypicalInfo.h"

struct FMonsterInherentInfo;


/**
 * 怪物属性基类
 */
class PAL4_API IMonsterProperty : public ICharacterProperty
{
protected:
    IMonsterProperty(const FCharacterBasicInfo&, const FMonsterTypicalInfo&);
    IMonsterProperty(const IMonsterProperty&) = default;
    IMonsterProperty(IMonsterProperty&&) = default;
    
    IMonsterProperty& operator=(const IMonsterProperty&) = default;
    IMonsterProperty& operator=(IMonsterProperty&&) = default;

public:
    bool IsDebuffImmune(EImmune) const override final;

    FMonsterTypicalInfo& TypicalInfo() { return MonsterTypicalInfo; }
    const FMonsterTypicalInfo& TypicalInfo() const { return MonsterTypicalInfo; }

    virtual const FMonsterInherentInfo& GetMonsterInherentInfo() const = 0;

private:
    FMonsterTypicalInfo MonsterTypicalInfo;
};
