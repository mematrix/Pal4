#pragma once

#include <Platform.h>


struct PAL4_API FGameArchive
{
    struct PAL4_API FCharacterArchive
    {
        int32 Level;
        int32 Experience;
        int32 HealthPoint;
        int32 ManaPoint;
        int32 CraftPoint;
        uint8 MagicPoints[5];
    };

    FCharacterArchive PropertyOfTianhe;
    FCharacterArchive PropertyOfLingsha;
    FCharacterArchive PropertyOfMengli;
    FCharacterArchive PropertyOfZiying;
};
