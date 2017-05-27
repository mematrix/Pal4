#pragma once

#include <functional>

#include <SharedPointer.h>

#include "Primitives/EnumType/ECharacterStatusType.h"

class IRoundManager;
class ICharacterTempStatus;
class ITempStatusOpWrapper;


class PAL4_API ICharacterTempStatusOperator
{
public:
    typedef std::function<int32(void*, ECharacterStatusType, int32, int32)> FTransformAction;

    virtual ~ICharacterTempStatusOperator() = default;

    virtual IRoundManager& GetRoundManager() = 0;

    virtual void AddTemporaryStatus(ECharacterStatusType, const TSharedRef<ITempStatusOpWrapper>&) = 0;

    virtual void RemoveTemporaryStatus(ECharacterStatusType, ITempStatusOpWrapper&) = 0;

    virtual ICharacterTempStatus& GetTempStatus() = 0;
};
