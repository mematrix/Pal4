// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterTempStatusManager.h"
#include "Combat/Interface/Character/ICharacterCombatDelegate.h"
#include "Combat/Interface/Character/ICharacterCombatContext.h"
#include "Combat/Interface/Character/ITempStatusOpWrapper.h"
#include "Character/ICharacterProperty.h"


FCharacterTempStatusManager::FCharacterTempStatusManager(ICharacterCombatDelegate& character) :
    ICharacterTempStatusOperator(),
    Character(character),
    TempStatus(character.GetProperty().StatusProperty()),
    StatusMap()
{
}

IRoundManager& FCharacterTempStatusManager::GetRoundManager()
{
    _ASSERT(Character.GetContext());
    return Character.GetContext()->GetRoundManager();
}

const IRoundManager& FCharacterTempStatusManager::GetRoundManager() const
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

FCharacterTemporaryStatus& FCharacterTempStatusManager::GetTempStatus()
{
    return TempStatus;
}
