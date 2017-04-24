// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterTempStatusManager.h"
#include "CombatDelegate/Character/ICharacterBattleDelegate.h"
#include "CombatDelegate/Character/ICharacterBattleContext.h"
#include "CombatDelegate/StatusOpWrapper/ITempStatusOpWrapper.h"


FCharacterTempStatusManager::FCharacterTempStatusManager(ICharacterBattleDelegate& character) :
    ICharacterTempStatusAccessor(),
    ICharacterTempStatusOperator(),
    Character(character),
    TempStatus(character.GetPersistentStatus()),
    StatusMap()
{
}

ICharacterRoundManager& FCharacterTempStatusManager::GetRoundManager()
{
    _ASSERT(Character.GetContext());
    return Character.GetContext()->GetRoundManager();
}

const ICharacterRoundManager& FCharacterTempStatusManager::GetRoundManager() const
{
    _ASSERT(Character.GetContext());
    return Character.GetContext()->GetRoundManager();
}

void FCharacterTempStatusManager::AddTemporaryStatus(ECharacterStatusType type, const TSharedRef<ITempStatusOpWrapper>& wrapper)
{
    auto oldWrapper = StatusMap.Find(static_cast<int32>(type));
    if (oldWrapper)
    {
        (*oldWrapper)->OnRemovingStatus(*this);
    }

    StatusMap.Add(static_cast<int32>(type), wrapper);
    wrapper->OnAddingStatus(*this);
}

void FCharacterTempStatusManager::RemoveTemporaryStatus(ECharacterStatusType type, ITempStatusOpWrapper& wrapper)
{
    auto existWrapper = StatusMap.Find(static_cast<int32>(type));
    if (existWrapper && (*existWrapper).operator->() == &wrapper)
    {
        StatusMap.Remove(static_cast<int32>(type));
        wrapper.OnRemovingStatus(*this);
    }
}

void FCharacterTempStatusManager::AddTransformer(void* key, ECharacterStatusType type, const FTransformAction& action)
{
    TempStatus.AddTransformer(key, type, action);
}

void FCharacterTempStatusManager::RemoveTransformer(void* key, ECharacterStatusType type)
{
    TempStatus.RemoveTransformer(key, type);
}

void FCharacterTempStatusManager::SetCommonBuffStatus(ECommonBuff value)
{
    TempStatus.SetCommonBuffStatus(value);
}

void FCharacterTempStatusManager::SetPoisonStatus(EPoison value)
{
    TempStatus.SetPoisonStatus(value);
}

void FCharacterTempStatusManager::SetControlledDebuffStatus(EControlledDebuff value)
{
    TempStatus.SetControlledDebuffStatus(value);
}

void FCharacterTempStatusManager::SetInVisibleStatus(bool value)
{
    TempStatus.SetInVisibleStatus(value);
}

void FCharacterTempStatusManager::SetReviveStatus(bool value)
{
    TempStatus.SetReviveStatus(value);
}

const FCharacterBattleStatus& FCharacterTempStatusManager::GetBattleStatus() const
{
    return TempStatus.GetBattleStatus();
}

int32 FCharacterTempStatusManager::GetPropertyValue(ECharacterStatusType type) const
{
    return TempStatus.GetPropertyValue(type);
}

const FCharacterStatusInfo& FCharacterTempStatusManager::GetAccumulatedInfo() const
{
    return TempStatus.GetAccumulatedInfo();
}
