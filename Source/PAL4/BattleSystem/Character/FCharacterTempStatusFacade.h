#pragma once

#include <functional>

#include "CharacterPrimitives/Model/ECharacterStatusType.h"
#include "CharacterPrimitives/Model/ECharacterBattleStatus.h"


class FCharacterTemporaryStatus;

class PAL4_API FCharacterTempStatusFacade
{
public:
    typedef std::function<int32(void*, ECharacterStatusType, int32, int32)> FTransformAction;

public:
    explicit FCharacterTempStatusFacade(FCharacterTemporaryStatus&);

    inline void AddTransformer(void*, ECharacterStatusType, const FTransformAction&);

    inline void RemoveTransformer(void* key, ECharacterStatusType type);

    inline void SetCommonBuffStatus(ECommonBuff value);

    inline void SetPoisonStatus(EPoison value);

    inline void SetControlledDebuffStatus(EControlledDebuff value);

    inline void SetInVisibleStatus(bool value);

    inline void SetReviveStatus(bool value);

private:
    FCharacterTemporaryStatus& TempStatus;
};
