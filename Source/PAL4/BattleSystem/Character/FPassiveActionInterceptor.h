#pragma once

#include <SharedPointer.h>

class ISingleAction;
class ICharacterBattleDelegate;
struct FBaseStatusModel;
struct FBaseAttackModel;
struct FBaseRestorerModel;

class PAL4_API FPassiveActionInterceptor
{
public:
    void BeforeComputeStatusResult(ISingleAction&, int32);

    TSharedRef<FBaseStatusModel> AfterComputeStatusResult(ISingleAction&, const TSharedRef<FBaseStatusModel>&, int32);

    void AfterStatusAction();

    void BeforeComputeAttackResult(ISingleAction&, int32);

    TSharedRef<FBaseAttackModel> AfterComputeAttackResult(ISingleAction&, const TSharedRef<FBaseAttackModel>&, int32);

    void AfterAttackAction();

    void BeforeComputeRestorerResult(ISingleAction&, int32);

    TSharedRef<FBaseRestorerModel> AfterComputeRestorerResult(ISingleAction&, const TSharedRef<FBaseRestorerModel>&, int32);

    void AfterRestorerAction();
};
