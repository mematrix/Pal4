// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include "FNormalAttackAction.h"
#include "Combat/Core/FCombatContext.h"


FNormalAttackAction::FNormalAttackAction(ICharacterDelegate& actor, const FTargetArray& targets, int32 count, int32 craftGrowth) :
    Actor(actor),
    Targets(targets),
    Count(count),
    CraftGrowthValue(craftGrowth),
    Helper(nullptr)
{
}

void FNormalAttackAction::BeforeDoAction()
{
    Helper = PrepareHelp();
    PrepareAttack();
}

void FNormalAttackAction::DoAction()
{
    int32 attackCount = 0;
    do
    {
        ++attackCount;
        for (int32 i = 0; i < Count; ++i)
        {
            for (ICharacterDelegate& del : Targets.Get())
            {
                //FCombatContext::GetBattleSystem()->DoAttackAction()
            }
        }
    } while (0);
}

void FNormalAttackAction::AfterDoAction()
{
    FinishAttack();
    if (Helper)
    {
        FinishHelp();
    }
}
