// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterTempStatusFacade.h"
#include "FCharacterTemporaryStatus.h"


FCharacterTempStatusFacade::FCharacterTempStatusFacade(FCharacterTemporaryStatus& status) :
    TempStatus(status)
{
}

void FCharacterTempStatusFacade::AddTransformer(void* key, ECharacterStatusType type, const FTransformAction& action)
{
    TempStatus.AddTransformer(key, type, action);
}

void FCharacterTempStatusFacade::RemoveTransformer(void* key, ECharacterStatusType type)
{
    TempStatus.RemoveTransformer(key, type);
}

void FCharacterTempStatusFacade::SetCommonBuffStatus(ECommonBuff value)
{
    TempStatus.SetCommonBuffStatus(value);
}

void FCharacterTempStatusFacade::SetPoisonStatus(EPoison value)
{
    TempStatus.SetPoisonStatus(value);
}

void FCharacterTempStatusFacade::SetControlledDebuffStatus(EControlledDebuff value)
{
    TempStatus.SetControlledDebuffStatus(value);
}

void FCharacterTempStatusFacade::SetInVisibleStatus(bool value)
{
    TempStatus.SetInVisibleStatus(value);
}

void FCharacterTempStatusFacade::SetReviveStatus(bool value)
{
    TempStatus.SetReviveStatus(value);
}
