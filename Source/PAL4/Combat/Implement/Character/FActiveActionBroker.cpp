// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <utility>

#include "../ActionCore/ISingleAction.h"
#include "FCombatCharacter.h"
#include "FActiveActionBroker.h"
#include "FPassiveActionInterceptor.h"

using namespace std::placeholders;

typedef void (FPassiveActionInterceptor::*CallBeforeInterceptor)(ISingleAction&, int32);

void CallBefore(const FActiveActionBroker* broker, CallBeforeInterceptor call,
    ISingleAction& action, ICharacterDelegate&, int32 type)
{
    (broker->GetPassiveCharacter()->GetActionInterceptor().*call)(action, type);
}

TSharedRef<FBaseAttackModel> CallAttackAfter(const FActiveActionBroker* broker, const ISingleAction& action,
    const TSharedRef<FBaseAttackModel>& ret, const ICharacterDelegate&, int32 type)
{
    return broker->GetPassiveCharacter()->GetActionInterceptor().AfterComputeAttackResult(action, ret, type);
}

TSharedRef<FBaseRestorerModel> CallRestorerAfter(const FActiveActionBroker* broker, const ISingleAction& action,
    const TSharedRef<FBaseRestorerModel>& ret, const ICharacterDelegate&, int32 type)
{
    return broker->GetPassiveCharacter()->GetActionInterceptor().AfterComputeRestorerResult(action, ret, type);
}

TSharedRef<FBaseStatusModel> CallStatusAfter(const FActiveActionBroker* broker, const ISingleAction& action,
    const TSharedRef<FBaseStatusModel>& ret, const ICharacterDelegate&, int32 type)
{
    return broker->GetPassiveCharacter()->GetActionInterceptor().AfterComputeStatusResult(action, ret, type);
}

FActiveActionBroker::FActiveActionBroker() :
    PassiveCharacter(nullptr),
    AttackComDelegate(&ISingleAction::ComputeAttackResult, nullptr, std::bind(CallAttackAfter, this, _1, _2, _3, _4)),
    RestorerComDelegate(&ISingleAction::ComputeRestorerResult, nullptr, std::bind(CallRestorerAfter, this, _1, _2, _3, _4)),
    StatusComDelegate(&ISingleAction::ComputeStatusResult, nullptr, std::bind(CallStatusAfter, this, _1, _2, _3, _4))
{
}
