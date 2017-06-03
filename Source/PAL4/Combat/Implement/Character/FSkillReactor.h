#pragma once

#include "Combat/Interface/Character/ISkillReactor.h"

class FCombatCharacter;


class PAL4_API FSkillReactor : public ISkillReactor
{
public:
    explicit FSkillReactor(FCombatCharacter&);
    FSkillReactor(const FSkillReactor&) = default;
    FSkillReactor(FSkillReactor&&) = default;

    FSkillReactor& operator=(const FSkillReactor&) = default;
    FSkillReactor& operator=(FSkillReactor&&) = default;

    void AmendResult(FSkillResult&) override;

    void OnBasicSkillFinished(const FBasicInfoResultRecord&) override;

    void OnStatusSkillFinished(const FStatusInfoResultRecord&) override;

    void OnTriggerSkillFinished(const FTriggerResultRecord&) override;

    void OnCombatStatusSkillFinished(const FCombatStatusResultRecord&) override;

    void TriggerSkill(const FSkillTriggerInfo&) override;

private:
    FCombatCharacter& Character;
};
