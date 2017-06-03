// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FStatusManager.h"
#include "Combat/Interface/Character/ICharacterDelegate.h"
#include "Combat/Interface/Character/ITempStatusOpWrapper.h"
#include "Character/ICharacterProperty.h"
#include "FCombatCharacter.h"


FStatusManager::FStatusManager(FCombatCharacter& character) :
    IStatusManager(),
    Character(character),
    TempStatus(character.GetCharacter().GetProperty().StatusProperty()),
    StatusMap()
{
}

void FStatusManager::SetStatusTransform(int32 skillID, ECharacterStatusType type, uint32 validNum, const std::function<int32(int32)>& func)
{
}

void FStatusManager::ClearSkillStatus(int32 skillID)
{
}

void FStatusManager::ClearSpecialStatus(ECharacterStatusType type)
{
}

void FStatusManager::ClearStatus(int32 skillID, ECharacterStatusType type)
{
}

void FStatusManager::SetBuff(EBuff buff, uint32 maxRoundNum)
{
}

void FStatusManager::SetPoison(EPoison poison, uint32 maxRoundNum)
{
}

void FStatusManager::SetDebuff(EDebuff debuff, uint32 maxRoundNum)
{
}

void FStatusManager::SetResurrect(bool canResurrct, uint32 maxRoundNum)
{
}

void FStatusManager::SetInvisible(bool invisible, uint32 maxRoundNum)
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
