#pragma once

#include <SharedPointer.h>

#include "../CharacterBridge/IPassiveActionInterceptor.h"


class PAL4_API FPassiveActionInterceptor : IPassiveActionInterceptor
{
public:
    explicit FPassiveActionInterceptor(ICharacterBattleDelegate&);
    FPassiveActionInterceptor(const FPassiveActionInterceptor&) = default;
    FPassiveActionInterceptor(FPassiveActionInterceptor&&) = default;

    FPassiveActionInterceptor& operator=(const FPassiveActionInterceptor&) = default;
    FPassiveActionInterceptor& operator=(FPassiveActionInterceptor&&) = default;

    TSharedRef<FBaseStatusModel> AfterComputeStatusResult(const ISingleAction&, const TSharedRef<FBaseStatusModel>&, int32);

    void AfterStatusAction(const ISingleAction&, const FBaseStatusModel&, int32);

    TSharedRef<FBaseAttackModel> AfterComputeAttackResult(const ISingleAction&, const TSharedRef<FBaseAttackModel>&, int32);

    void AfterAttackAction(const ISingleAction&, const FBaseAttackModel&, int32);

    TSharedRef<FBaseRestorerModel> AfterComputeRestorerResult(const ISingleAction&, const TSharedRef<FBaseRestorerModel>&, int32);

    void AfterRestorerAction(const ISingleAction&, const FBaseRestorerModel&, int32);

    FStatusInterceptorFunc SetStatusInterceptor(const FStatusInterceptorFunc&) override;
    FAttackInterceptorFunc SetAttackInterceptor(const FAttackInterceptorFunc&) override;
    FRestorerInterceptorFunc SetRestorerInterceptor(const FRestorerInterceptorFunc&) override;

private:
    FStatusInterceptorFunc StatusFunc;
    FAttackInterceptorFunc AttackFunc;
    FRestorerInterceptorFunc RestorerFunc;
};
