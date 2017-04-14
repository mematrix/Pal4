// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <algorithm>

#include "Util/EventUtil.h"

#include "FBattleSystem.h"
#include "CharacterBridge/ICharacterPropertyManager.h"
#include "Character/FBattleCharacter.h"
#include "AttackCore/FBaseRestorerModel.h"
#include "AttackCore/FBaseStatusModel.h"
#include "AttackCore/FMagicAttackModel.h"
#include "AttackCore/FNormalAttackModel.h"
#include "AttackCore/FSkillAttackModel.h"
#include "AttackCore/FPropAttackModel.h"


class PAL4_API RoundDispatcherRaii
{
    ICharacterRoundDispatcher& Dispatcher;

public:
    explicit RoundDispatcherRaii(ICharacterRoundDispatcher& dispatcher) : Dispatcher(dispatcher) { }
    ~RoundDispatcherRaii() { Dispatcher.OnBattleFinished(); }
};


FBattleSystem::FBattleSystem(const TArray<TSharedRef<ICharacterBattleDelegate>>& characters,
    const TSharedRef<ICharacterRoundDispatcher>& dispatcher) :
    BattleBeginEvent(),
    BattleFinishedEvent(),
    CharacterWillActEvent(),
    CharacterFinishActEvent(),
    Characters(),
    Dispatcher(dispatcher),
    CustomStatusFunc(),
    CustomAttackFunc(),
    CustomRestorerFunc(),
    CharacterActLast(nullptr)
{
    auto count = characters.Num();
    for (int i = 0; i < count; ++i)
    {
        Characters.Emplace(MakeShared<FBattleCharacter>(characters[i]));
    }
}

FBattleSystem::~FBattleSystem()
{
}

void FBattleSystem::AddCharacter(const TSharedRef<ICharacterBattleDelegate>& characterDelegate)
{
    auto character = MakeShared<FBattleCharacter>(characterDelegate);
    Characters.Add(character);
    Dispatcher->AddCharacter(character);
}

void FBattleSystem::Run()
{
    InvokeEvent(BattleBeginEvent, *this);

    // 不应该出现这种情况
    _ASSERT(!BattleIsOver());

    {
        RoundDispatcherRaii dispatcherRaii(Dispatcher.Get());
        Dispatcher->OnBattleBegin(Characters);

        FBattleCharacter* characterActLast = nullptr;
        while (!BattleIsOver())
        {
            FBattleCharacter& character = Dispatcher->MoveToNext();
            characterActLast = &character;

            InvokeEvent(CharacterWillActEvent, *this, character.GetCharacterDelegate());

            auto& roundManager = character.GetRoundManager();
            roundManager.DoRoundAction();

            InvokeEvent(CharacterFinishActEvent, *this, character.GetCharacterDelegate());
        }

        CharacterActLast = characterActLast;
    }

    InvokeEvent(BattleFinishedEvent, *this);
}

void FBattleSystem::SetStatusResultCallback(const std::function<void(int32, ICharacterBattleDelegate&, const FBaseStatusModel&)>& func)
{
    CustomStatusFunc = func;
}

void FBattleSystem::ApplyStatusResult(int32 type, ICharacterBattleDelegate& character, const FBaseStatusModel& model)
{
    if (0 == type)
    {
        //
    }
    else
    {
        if (CustomStatusFunc)
        {
            CustomStatusFunc(type, character, model);
        }
    }
}

void FBattleSystem::SetAttackResultCallback(const std::function<void(int32, ICharacterBattleDelegate&, const FBaseAttackModel&)>& func)
{
    CustomAttackFunc = func;
}

void FBattleSystem::ApplyAttackResult(int32 type, ICharacterBattleDelegate& character, const FBaseAttackModel& model)
{
    switch (type)
    {
    case 0:
    {
        const auto& normalModel = static_cast<const FNormalAttackModel&>(model);
        //
        break;
    }

    case 1:
    {
        const auto& maginModel = static_cast<const FMagicAttackModel&>(model);
        //
        break;
    }

    case 2:
    {
        const auto& skillModel = static_cast<const FSkillAttackModel&>(model);
        //
        break;
    }

    case 3:
    {
        const auto& propModel = static_cast<const FPropAttackModel&>(model);
        //
        break;
    }

    default:
    {
        if (CustomAttackFunc)
        {
            CustomAttackFunc(type, character, model);
        }
        break;
    }
    }
}

void FBattleSystem::SetRestorerResultCallback(const std::function<void(int32, ICharacterBattleDelegate&, const FBaseRestorerModel&)>& func)
{
    CustomRestorerFunc = func;
}

void FBattleSystem::ApplyRestorerResult(int32 type, ICharacterBattleDelegate& character, const FBaseRestorerModel& model)
{
    if (0 == type)
    {
        //
    }
    else
    {
        if (CustomRestorerFunc)
        {
            CustomRestorerFunc(type, character, model);
        }
    }
}

int32 FBattleSystem::StatAliveStatus() const
{
    int32 playerAlive = 0x0;
    int32 nonPlayerAlive = 0x0;
    for (int i = 0; i < Characters.Num(); ++i)
    {
        auto& manager = Characters[i]->GetCharacterDelegate().GetPropertyManager();
        if (manager.IsAlive())
        {
            if (manager.IsPlayer())
            {
                playerAlive = 1 << 0;
            }
            else
            {
                nonPlayerAlive = 1 << 1;
            }
        }
    }

    return playerAlive | nonPlayerAlive;
}

bool FBattleSystem::BattleIsOver() const
{
    return StatAliveStatus() != 3;
}

bool FBattleSystem::IsPlayerWinned() const
{
    if (nullptr == CharacterActLast)
    {
        return false;
    }

    int32 status = StatAliveStatus();

    if (1 == status)
    {
        return true;
    }
    if (2 == status)
    {
        return false;
    }
    return CharacterActLast->GetCharacterDelegate().GetPropertyManager().IsPlayer();
}
