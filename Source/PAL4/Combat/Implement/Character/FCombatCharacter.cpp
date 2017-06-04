// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCombatCharacter.h"
#include "Character/ICharacterProperty.h"


FCombatCharacter::FCombatCharacter(const TSharedRef<ICharacterDelegate>& character) :
    ICombatContext(),
    CharacterDelegate(character),
    RoundManager(character.Get()),
    TempStatus(character->GetProperty().StatusProperty()),
    SkillRoundRecord()
{
}

void FCombatCharacter::OnBattleBegin()
{
    CharacterDelegate->BeginBattle(*this);
}

void FCombatCharacter::OnBattleFinished()
{
    CharacterDelegate->FinishBattle();
}

void FCombatCharacter::SetStatusTransform(int32 skillID, ECharacterStatusType type, uint32 validNum, const std::function<int32(int32)>& func)
{
    SkillRoundRecord.remove_if([skillID, type, this](const FSkillRoundRecord& record) -> bool
    {
        if (skillID == record.SkillID && type == record.Type)
        {
            RoundManager.RemoveDelayCallFunc(record.RoundFuncKey);
            return true;
        }

        return false;
    });


}

void FCombatCharacter::ClearSkillStatus(int32 skillID)
{
}

void FCombatCharacter::ClearSpecialStatus(ECharacterStatusType type)
{
}

void FCombatCharacter::ClearStatus(int32 skillID, ECharacterStatusType type)
{
}

void FCombatCharacter::SetBuff(EBuff buff, uint32 maxRoundNum)
{
}

void FCombatCharacter::SetPoison(EPoison poison, uint32 maxRoundNum)
{
}

void FCombatCharacter::SetDebuff(EDebuff debuff, uint32 maxRoundNum)
{
}

void FCombatCharacter::SetResurrect(bool canResurrct, uint32 maxRoundNum)
{
}

void FCombatCharacter::SetInvisible(bool invisible, uint32 maxRoundNum)
{
}

void FCombatCharacter::AmendResult(FSkillResult&, const ISkill&)
{
}

void FCombatCharacter::OnBasicSkillFinished(const FBasicInfoResultRecord&)
{
}

void FCombatCharacter::OnStatusSkillFinished(const FStatusInfoResultRecord&)
{
}

void FCombatCharacter::OnTriggerSkillFinished(const FTriggerResultRecord&)
{
}

void FCombatCharacter::OnCombatStatusSkillFinished(const FCombatStatusResultRecord&)
{
}

void FCombatCharacter::TriggerSkill(const FSkillTriggerInfo&)
{
}
