#pragma once

#include <SharedPointer.h>

class IRoleProperty;
class IMonsterProperty;
struct FCharacterArchive;


/**
 * 角色工厂类
 */
class PAL4_API ICharacterFactory
{
public:
    virtual ~ICharacterFactory() = default;

    virtual TSharedRef<IRoleProperty> CreateRole(int32 id, const FCharacterArchive& archive) const = 0;

    virtual TSharedRef<IMonsterProperty> CreateMonster(int32 id) const = 0;
};
