// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FCombatCharacter.h"
#include "Character/ICharacterProperty.h"
#include "Skill/Enum/ESkillTriggerType.h"
#include "Skill/Model/FSkillTriggerInfo.h"


FCombatCharacter::FCombatCharacter(const TSharedRef<ICharacterDelegate>& character) :
    ICombatContext(),
    CharacterDelegate(character),
    RoundManager(character.Get()),
    TempStatus(character->GetProperty().StatusProperty()),
    SkillRoundRecords(),
    RoundFuncKeyBuff(0),
    RoundFuncKeyPoison(0),
    RoundFuncKeyDebuff(0),
    RoundFuncKeyResurrect(0),
    RoundFuncKeyInvisible(0)
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
    SkillRoundRecords.remove_if([skillID, type, this](const FSkillRoundRecord& record) -> bool
    {
        if (skillID == record.SkillID && type == record.Type)
        {
            RoundManager.RemoveDelayCallFunc(record.RoundFuncKey);
            return true;
        }

        return false;
    });

    auto key = RoundManager.AddDelayCallFunc(validNum, false, [this, skillID, type] {
        this->ClearStatus(skillID, type);
    });
    SkillRoundRecords.emplace_back(skillID, type, key);
    TempStatus.AddOrUpdateTransformer(skillID, type, func);
}

void FCombatCharacter::ClearSkillStatus(int32 skillID)
{
    TempStatus.RemoveTransformerByKey(skillID);

    SkillRoundRecords.remove_if([skillID, this](const FSkillRoundRecord& record) -> bool
    {
        if (skillID == record.SkillID)
        {
            RoundManager.RemoveDelayCallFunc(record.RoundFuncKey);
            return true;
        }

        return false;
    });
}

void FCombatCharacter::ClearSpecialStatus(ECharacterStatusType type)
{
    TempStatus.RemoveTransformerByStatus(type);

    SkillRoundRecords.remove_if([type, this](const FSkillRoundRecord& record) -> bool {
        if (type == record.Type)
        {
            RoundManager.RemoveDelayCallFunc(record.RoundFuncKey);
            return true;
        }

        return false;
    });
}

void FCombatCharacter::ClearStatus(int32 skillID, ECharacterStatusType type)
{
    TempStatus.RemoveTransformer(skillID, type);

    SkillRoundRecords.remove_if([skillID, type, this](const FSkillRoundRecord& record) -> bool {
        if (skillID == record.SkillID && type == record.Type)
        {
            RoundManager.RemoveDelayCallFunc(record.RoundFuncKey);
            return true;
        }

        return false;
    });
}

void FCombatCharacter::SetBuff(EBuff buff, uint32 maxRoundNum)
{
    if (EBuff::None != TempStatus.GetBuffStatus())
    {
        RoundManager.RemoveDelayCallFunc(RoundFuncKeyBuff);
    }

    TempStatus.SetBuffStatus(buff);
    // TODO: 根据Buff值，添加对应的被动触发技能、以及修正伤害结果的函数
    if (EBuff::None != buff)
    {
        RoundFuncKeyBuff = RoundManager.AddDelayCallFunc(maxRoundNum, false, [this] {
            this->SetBuff(EBuff::None, 0);
        });
    }
}

void FCombatCharacter::SetPoison(EPoison poison, uint32 maxRoundNum)
{
    if (EPoison::None != TempStatus.GetPoisonStatus())
    {
        RoundManager.RemoveDelayCallFunc(RoundFuncKeyPoison);
    }

    TempStatus.SetPoisonStatus(poison);
    if (EPoison::None != poison)
    {
        RoundFuncKeyPoison = RoundManager.AddDelayCallFunc(maxRoundNum, false, [this] {
            this->SetPoison(EPoison::None, 0);
        });
    }
}

void FCombatCharacter::SetDebuff(EDebuff debuff, uint32 maxRoundNum)
{
    if (EDebuff::None != TempStatus.GetDebuffStatus())
    {
        RoundManager.RemoveDelayCallFunc(RoundFuncKeyDebuff);
    }

    TempStatus.SetDebuffStatus(debuff);
    if (EDebuff::None != debuff)
    {
        RoundFuncKeyDebuff = RoundManager.AddDelayCallFunc(maxRoundNum, false, [this] {
            this->SetDebuff(EDebuff::None, 0);
        });
    }
}

void FCombatCharacter::SetResurrect(bool canResurrct, uint32 maxRoundNum)
{
    if (TempStatus.CanResurrect())
    {
        RoundManager.RemoveDelayCallFunc(RoundFuncKeyResurrect);
    }

    TempStatus.SetResurrectStatus(canResurrct);
    if (canResurrct)
    {
        RoundFuncKeyResurrect = RoundManager.AddDelayCallFunc(maxRoundNum, false, [this] {
            this->SetResurrect(false, 0);
        });
    }
}

void FCombatCharacter::SetInvisible(bool invisible, uint32 maxRoundNum)
{
    if (TempStatus.IsInvisible())
    {
        RoundManager.RemoveDelayCallFunc(RoundFuncKeyInvisible);
    }

    TempStatus.SetInvisibleStatus(invisible);
    if (invisible)
    {
        RoundFuncKeyInvisible = RoundManager.AddDelayCallFunc(maxRoundNum, false, [this] {
            this->SetInvisible(false, 0);
        });
    }
}

void FCombatCharacter::AmendResult(FSkillResult& result, const ISkill& skill)
{
    for (const auto& func : AmendFuncs)
    {
        if (func)
        {
            func(result, skill);
        }
    }
}

void FCombatCharacter::OnBasicSkillFinished(const FBasicInfoResultRecord& record)
{
    for (const auto& func : BasicInfoFinishedFuncs)
    {
        if (func)
        {
            func(record);
        }
    }
}

void FCombatCharacter::OnStatusSkillFinished(const FStatusInfoResultRecord& record)
{
    for (const auto& func : StatusInfoFinishedFuncs)
    {
        if (func)
        {
            func(record);
        }
    }
}

void FCombatCharacter::OnTriggerSkillFinished(const FTriggerResultRecord& record)
{
    for (const auto& func : TriggerFinishedFuncs)
    {
        if (func)
        {
            func(record);
        }
    }
}

void FCombatCharacter::OnCombatStatusSkillFinished(const FCombatStatusResultRecord& record)
{
    for (const auto& func : CombatStatusFinishedFuncs)
    {
        if (func)
        {
            func(record);
        }
    }
}

//static ESkillTriggerType GetTriggerType(ESkillSource source, bool isActor)
//{
//    switch (source)
//    {
//    case ESkillSource::Physical:
//        return isActor ? ESkillTriggerType
//        break;
//    case ESkillSource::Stunt: break;
//    case ESkillSource::Prop: break;
//    case ESkillSource::Prescription: break;
//    case ESkillSource::WaterMagic: break;
//    case ESkillSource::FireMagic: break;
//    case ESkillSource::ThunderMagic: break;
//    case ESkillSource::WindMagic: break;
//    case ESkillSource::SoilMagic: break;
//    case ESkillSource::Trigger: break;
//    default: ;
//    }
//}

void FCombatCharacter::TriggerSkill(const FSkillTriggerInfo& info, bool isActor)
{
    //
}

void FCombatCharacter::AddTriggerSkill(int32 skillID)
{
    // TODO: 使用技能ID查找技能触发信息，然后加入Map存储
}

void FCombatCharacter::RemoveTriggerSkill(int32 skillID)
{
}
