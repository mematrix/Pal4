#pragma once

#include <Platform.h>

class IRoleProperty;


class PAL4_API FLevelManager
{
public:
    void AddRoleExperience(IRoleProperty&, int32);
};
