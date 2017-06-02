// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "Util/EventUtil.h"

#include "FSkillReactor.h"


FSkillReactor::FSkillReactor(ICharacterDelegate& character) :
    ISkillReactor(character),
    StatusFunc(),
    AttackFunc(),
    RestorerFunc()
{
}

TSharedRef<FBaseStatusModel> FSkillReactor::AfterComputeStatusResult(const ISingleAction& action,
    const TSharedRef<FBaseStatusModel>& model, int32 type)
{
    if (!StatusFunc)
    {
        return model;
    }

    return StatusFunc(*this, action, model, type);
}

void FSkillReactor::AfterStatusAction(const ISingleAction& action, const FBaseStatusModel& model, int32 type)
{
    InvokeEvent(OnStatusActionFinishedEvent, *this, action, model, type);
}

TSharedRef<FBaseAttackModel> FSkillReactor::AfterComputeAttackResult(const ISingleAction& action,
    const TSharedRef<FBaseAttackModel>& model, int32 type)
{
    if (!AttackFunc)
    {
        return model;
    }

    return AttackFunc(*this, action, model, type);
}

void FSkillReactor::AfterAttackAction(const ISingleAction& action, const FBaseAttackModel& model, int32 type)
{
    InvokeEvent(OnAttackActionFinishedEvent, *this, action, model, type);
}

TSharedRef<FBaseRestorerModel> FSkillReactor::AfterComputeRestorerResult(const ISingleAction& action,
    const TSharedRef<FBaseRestorerModel>& model, int32 type)
{
    if (!RestorerFunc)
    {
        return model;
    }

    return RestorerFunc(*this, action, model, type);
}

void FSkillReactor::AfterRestorerAction(const ISingleAction& action, const FBaseRestorerModel& model, int32 type)
{
    InvokeEvent(OnRestorerActionFinishedEvent, *this, action, model, type);
}

ISkillReactor::FStatusInterceptorFunc FSkillReactor::SetStatusInterceptor(const FStatusInterceptorFunc& func)
{
    auto ret = StatusFunc;
    StatusFunc = func;

    return ret;
}

ISkillReactor::FAttackInterceptorFunc FSkillReactor::SetAttackInterceptor(const FAttackInterceptorFunc& func)
{
    auto ret = AttackFunc;
    AttackFunc = func;

    return ret;
}

ISkillReactor::FRestorerInterceptorFunc FSkillReactor::SetRestorerInterceptor(const FRestorerInterceptorFunc& func)
{
    auto ret = RestorerFunc;
    RestorerFunc = func;

    return ret;
}
