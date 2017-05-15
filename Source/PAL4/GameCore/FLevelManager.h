#pragma once

#include <Platform.h>

class IRoleProperty;


class PAL4_API FLevelManager
{
public:
    static void AddRoleExperience(IRoleProperty&, int32);
};
