#pragma once

#include <list>
#include <map>

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

private:
    TSharedRef<ICharacterDelegate> CharacterDelegate;
    FRoundManager RoundManager;


    /* ICombatContext begin */
public:
    ICharacterDelegate& GetCharacter() override { return CharacterDelegate.Get(); }

    FRoundManager& GetRoundManager() override { return RoundManager; }

    ISkillReactor& GetSkillReactor() override { return *this; }

    IStatusManager& GetStatusManager() override { return *this; }

    /* ICombatContext end */


    /* IStatusManager begin */
private:
    struct PAL4_API FSkillRoundRecord
    {
        int32 SkillID;
        ECharacterStatusType Type;
        uint32 RoundFuncKey;

        FSkillRoundRecord(int32 id, ECharacterStatusType type, uint32 key) :
            SkillID(id),
            Type(type),
            RoundFuncKey(key)
        {
        }
    };

    FTemporaryStatus TempStatus;
    std::list<FSkillRoundRecord> SkillRoundRecords;
    uint32 RoundFuncKeyBuff;
    uint32 RoundFuncKeyPoison;
    uint32 RoundFuncKeyDebuff;
    uint32 RoundFuncKeyResurrect;
    uint32 RoundFuncKeyInvisible;

public:
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

    /* IStatusManager end */


    /* ISkillReactor begin */
private:
    template<typename T>
    using TSkillFuncList = std::list<std::function<void(const T&)>>;

    std::list<std::function<void(FSkillResult&, const ISkill&)>> AmendFuncs;

    TSkillFuncList<FBasicInfoResultRecord> BasicInfoFinishedFuncs;
    TSkillFuncList<FStatusInfoResultRecord> StatusInfoFinishedFuncs;
    TSkillFuncList<FTriggerResultRecord> TriggerFinishedFuncs;
    TSkillFuncList<FCombatStatusResultRecord> CombatStatusFinishedFuncs;
    std::map<int32, std::list<int32>> TriggerSkillMap;

public:
    void AmendResult(FSkillResult&, const ISkill&) override;

    void OnBasicSkillFinished(const FBasicInfoResultRecord&) override;

    void OnStatusSkillFinished(const FStatusInfoResultRecord&) override;

    void OnTriggerSkillFinished(const FTriggerResultRecord&) override;

    void OnCombatStatusSkillFinished(const FCombatStatusResultRecord&) override;

    void TriggerSkill(const FSkillTriggerInfo&, bool) override;

private:
    void AddTriggerSkill(int32 skillID);

    void RemoveTriggerSkill(int32 skillID);

    /* ISkillReactor end */
};
