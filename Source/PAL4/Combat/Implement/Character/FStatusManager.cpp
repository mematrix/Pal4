// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FStatusManager.h"
#include "Combat/Interface/Character/ICharacterDelegate.h"
#include "Combat/Interface/Character/ICombatContext.h"
#include "Combat/Interface/Character/ITempStatusOpWrapper.h"
#include "Character/ICharacterProperty.h"


FStatusManager::FStatusManager(ICharacterDelegate& character) :
    ICharacterTempStatusOperator(),
    Character(character),
    TempStatus(character.GetProperty().StatusProperty()),
    StatusMap()
{
}

IRoundManager& FStatusManager::GetRoundManager()
{
    _ASSERT(Character.GetContext());
    return Character.GetContext()->GetRoundManager();
}

const IRoundManager& FStatusManager::GetRoundManager() const
{
    _ASSERT(Character.GetContext());
    return Character.GetContext()->GetRoundManager();
}

void FStatusManager::AddTemporaryStatus(ECharacterStatusType type, const TSharedRef<ITempStatusOpWrapper>& wrapper)
{
    auto oldWrapper = StatusMap.Find(static_cast<int32>(type));
    if (oldWrapper)
    {
        (*oldWrapper)->OnRemovingStatus(*this);
    }

    StatusMap.Add(static_cast<int32>(type), wrapper);
    wrapper->OnAddingStatus(*this);
}

void FStatusManager::RemoveTemporaryStatus(ECharacterStatusType type, ITempStatusOpWrapper& wrapper)
{
    auto existWrapper = StatusMap.Find(static_cast<int32>(type));
    if (existWrapper && (*existWrapper).operator->() == &wrapper)
    {
        StatusMap.Remove(static_cast<int32>(type));
        wrapper.OnRemovingStatus(*this);
    }
}

FTemporaryStatus& FStatusManager::GetTempStatus()
{
    return TempStatus;
}
