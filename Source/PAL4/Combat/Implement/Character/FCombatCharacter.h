#pragma once

#include <SharedPointer.h>

#include "Combat/Interface/Character/ICombatContext.h"
#include "Combat/Interface/Character/IStatusManager.h"
#include "Combat/Interface/Character/ISkillReactor.h"
#include "Combat/Interface/Character/ICharacterDelegate.h"
#include "../Round/FRoundManager.h"
#include "FTemporaryStatus.h"


class PAL4_API FCombatCharacter : public ICombatContext, public IStatusManager, public ISkillReactor
{
public:
    explicit FCombatCharacter(const TSharedRef<ICharacterDelegate>&);
    FCombatCharacter(const FCombatCharacter&) = delete;
    FCombatCharacter(FCombatCharacter&&) = default;

    FCombatCharacter& operator=(const FCombatCharacter&) = delete;
    FCombatCharacter& operator=(FCombatCharacter&&) = default;

    void OnBattleBegin();

    void OnBattleFinished();

    ICharacterDelegate& GetCharacter() override { return CharacterDelegate.Get(); }

    FRoundManager& GetRoundManager() override { return RoundManager; }

    const FRoundManager& GetRoundManager() const { return RoundManager; }

    ISkillReactor& GetSkillReactor() override { return *this; }

    IStatusManager& GetStatusManager() override { return *this; }

    const FTemporaryStatus& GetTempStatus() const override { return TempStatus; }

    void SetStatusTransform(int32 skillID, ECharacterStatusType type, uint32 validNum, const std::function<int32(int32)>& func) override;

    void ClearSkillStatus(int32 skillID) override;

    void ClearSpecialStatus(ECharacterStatusType type) override;

    void ClearStatus(int32 skillID, ECharacterStatusType type) override;

    void SetBuff(EBuff buff, uint32 maxRoundNum) override;

    void SetPoison(EPoison poison, uint32 maxRoundNum) override;

    void SetDebuff(EDebuff debuff, uint32 maxRoundNum) override;

    void SetResurrect(bool canResurrct, uint32 maxRoundNum) override;

    void SetInvisible(bool invisible, uint32 maxRoundNum) override;

    void AmendResult(FSkillResult&) override;

    void OnBasicSkillFinished(const FBasicInfoResultRecord&) override;

    void OnStatusSkillFinished(const FStatusInfoResultRecord&) override;

    void OnTriggerSkillFinished(const FTriggerResultRecord&) override;

    void OnCombatStatusSkillFinished(const FCombatStatusResultRecord&) override;

    void TriggerSkill(const FSkillTriggerInfo&) override;

private:
    TSharedRef<ICharacterDelegate> CharacterDelegate;
    FRoundManager RoundManager;
    FTemporaryStatus TempStatus;
};
