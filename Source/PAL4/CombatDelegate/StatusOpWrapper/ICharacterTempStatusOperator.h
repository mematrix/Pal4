#pragma once

#include <functional>

#include <SharedPointer.h>

#include "CharacterPrimitives/Model/ECharacterStatusType.h"
#include "CharacterPrimitives/Model/ECharacterBattleStatus.h"

class ICharacterRoundManager;
class ITempStatusOpWrapper;


class PAL4_API ICharacterTempStatusOperator
{
public:
    typedef std::function<int32(void*, ECharacterStatusType, int32, int32)> FTransformAction;

    virtual ~ICharacterTempStatusOperator()
    {
    }

    virtual ICharacterRoundManager& GetRoundManager() = 0;

    virtual void AddTemporaryStatus(ECharacterStatusType, const TSharedRef<ITempStatusOpWrapper>&) = 0;

    virtual void RemoveTemporaryStatus(ECharacterStatusType, ITempStatusOpWrapper&) = 0;

    virtual void AddTransformer(void*, ECharacterStatusType, const FTransformAction&) = 0;

    virtual void RemoveTransformer(void* key, ECharacterStatusType type) = 0;

    virtual void SetCommonBuffStatus(ECommonBuff value) = 0;

    virtual void SetPoisonStatus(EPoison value) = 0;

    virtual void SetControlledDebuffStatus(EControlledDebuff value) = 0;

    virtual void SetInVisibleStatus(bool value) = 0;

    virtual void SetReviveStatus(bool value) = 0;
};
