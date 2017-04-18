// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <utility>

#include "FBattleCharacter.h"
#include "FActiveActionBroker.h"
#include "FPassiveActionInterceptor.h"

using namespace std::placeholders;

typedef void (FPassiveActionInterceptor::*CallBeforeInterceptor)(ISingleAction&, int32);

void CallBefore(const FActiveActionBroker* broker, CallBeforeInterceptor call,
    ISingleAction& action, ICharacterBattleDelegate&, int32 type)
{
    broker->GetPassiveCharacter()->GetActionInterceptor().*call(action, type);
}

TSharedRef<FBaseAttackModel> CallAttackAfter(const FActiveActionBroker* broker, ISingleAction& action,
    const TSharedRef<FBaseAttackModel>& ret, ICharacterBattleDelegate&, int32 type)
{
    return broker->GetPassiveCharacter()->GetActionInterceptor().AfterComputeAttackResult(action, ret, type);
}

TSharedRef<FBaseRestorerModel> CallRestorerAfter(const FActiveActionBroker* broker, ISingleAction& action,
    const TSharedRef<FBaseRestorerModel>& ret, ICharacterBattleDelegate&, int32 type)
{
    return broker->GetPassiveCharacter()->GetActionInterceptor().AfterComputeRestorerResult(action, ret, type);
}

TSharedRef<FBaseStatusModel> CallStatusAfter(const FActiveActionBroker* broker, ISingleAction& action,
    const TSharedRef<FBaseStatusModel>& ret, ICharacterBattleDelegate&, int32 type)
{
    return broker->GetPassiveCharacter()->GetActionInterceptor().AfterComputeStatusResult(action, ret, type);
}

FActiveActionBroker::FActiveActionBroker() :
    ActiveCharacter(nullptr),
    PassiveCharacter(nullptr),
    AttackComDelegate(&ISingleAction::ComputeAttackResult,
        std::bind(CallBefore, this, &FPassiveActionInterceptor::BeforeComputeAttackResult, _1, _2, _3),
            std::bind(CallAttackAfter, this, _1, _2, _3, _4)),
    RestorerComDelegate(&ISingleAction::ComputeRestorerResult,
        std::bind(CallBefore, this, &FPassiveActionInterceptor::BeforeComputeRestorerResult, _1, _2, _3),
            std::bind(CallRestorerAfter, this, _1, _2, _3, _4)),
    StatusComDelegate(&ISingleAction::ComputeStatusResutl,
        std::bind(CallBefore, this, &FPassiveActionInterceptor::BeforeComputeStatusResult, _1, _2, _3),
            std::bind(CallStatusAfter, this, _1, _2, _3, _4))
{
}
