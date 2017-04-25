#pragma once

#include <SharedPointer.h>

#include "Util/MacroUtil.h"
#include "Primitives/EnumType/ECharacterStatusType.h"

class ITempStatusOpWrapper;


struct PAL4_API FBaseStatusModel
{
    FBaseStatusModel(ECharacterStatusType type, const TSharedRef<ITempStatusOpWrapper>& wrapper) :
        StatusType(type),
        TempStatusOpWrapper(wrapper)
    {
    }

    MAKE_DEFAULT_COPY_CTOR_AND_OP(FBaseStatusModel)

    // ����״̬����
    ECharacterStatusType StatusType;
    // ����Wrapper
    TSharedRef<ITempStatusOpWrapper> TempStatusOpWrapper;
};
