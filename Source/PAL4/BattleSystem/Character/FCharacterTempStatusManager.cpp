// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCharacterTempStatusManager.h"
#include "FBattleCharacter.h"


FCharacterTempStatusManager::FCharacterTempStatusManager(FBattleCharacter& character) :
    Character(character),
    TempStatusFacade(character.GetTemporaryStatus()),
    StatusMap()
{
}

ICharacterBattleDelegate& FCharacterTempStatusManager::GetCharacter()
{
    return Character.GetCharacterDelegate();
}

const ICharacterBattleDelegate& FCharacterTempStatusManager::GetCharacter() const
{
    return Character.GetCharacterDelegate();
}

ICharacterRoundManager& FCharacterTempStatusManager::GetRoundManager()
{
    return Character.GetRoundManager();
}

const ICharacterRoundManager& FCharacterTempStatusManager::GetRoundManager() const
{
    return Character.GetRoundManager();
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

void FCharacterTempStatusManager::RemoveTemporaryStatus(ECharacterStatusType type, const ITempStatusOpWrapper& wrapper)
{
    auto existWrapper = StatusMap.Find(static_cast<int32>(type));
    if (existWrapper && (*existWrapper).operator->() == &wrapper)
    {
        StatusMap.Remove(static_cast<int32>(type));
    }
}
