#pragma once

#include <SharedPointer.h>

#include "../CharacterBridge/IPassiveActionInterceptor.h"


class PAL4_API FPassiveActionInterceptor : IPassiveActionInterceptor
{
public:
    TSharedRef<FBaseStatusModel> AfterComputeStatusResult(ISingleAction&, const TSharedRef<FBaseStatusModel>&, int32);

    void AfterStatusAction();

    TSharedRef<FBaseAttackModel> AfterComputeAttackResult(ISingleAction&, const TSharedRef<FBaseAttackModel>&, int32);

    void AfterAttackAction();

    TSharedRef<FBaseRestorerModel> AfterComputeRestorerResult(ISingleAction&, const TSharedRef<FBaseRestorerModel>&, int32);

    void AfterRestorerAction();
};
