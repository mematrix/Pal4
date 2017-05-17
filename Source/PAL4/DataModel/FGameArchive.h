#pragma once

#include <map>

#include <Platform.h>


struct PAL4_API FCharacterArchive
{
    int32 Level;
    int32 Experience;
    int32 HealthPoint;
    int32 ManaPoint;
    int32 CraftPoint;
    // 对他人好感度
    uint32 Favors;
    uint8 MagicPoints[5];
};


struct PAL4_API FGameArchive
{
    std::map<int32, FCharacterArchive> CharacterArchives;
};
