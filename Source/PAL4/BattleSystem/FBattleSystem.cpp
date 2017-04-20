// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <algorithm>

#include "Util/EventUtil.h"

#include "FBattleSystem.h"
#include "CharacterBridge/ICharacterPropertyManager.h"
#include "Character/FBattleCharacter.h"
#include "ActionCore/FBaseAttackModel.h"
#include "ActionCore/FBaseRestorerModel.h"
#include "ActionCore/FBaseStatusModel.h"
#include "ActionCore/ISingleAction.h"


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

void FBattleSystem::ApplyAttackResult(const ISingleAction& action, ICharacterBattleDelegate& character,
    const FBaseAttackModel& model, int32 type)
{
    auto battleCharacter = FindCharacter(&character);
    if (!battleCharacter)
    {
        _ASSERT(0);
        return;
    }

    if (static_cast<uint32>(type) <= 3)
    {
        auto& propertyManager = character.GetPropertyManager();
        propertyManager.AddHealthValue(-model.TotalValue);
    }
    else
    {
        action.CustomApplyAttackResult(character, model, type);
    }

    //model.Releaser->OnAttackActionFinished(model);
    (*battleCharacter)->GetActionInterceptor().AfterAttackAction(action, model, type);
}

void FBattleSystem::ApplyRestorerResult(const ISingleAction& action, ICharacterBattleDelegate& character,
    const FBaseRestorerModel& model, int32 type)
{
    auto battleCharacter = FindCharacter(&character);
    if (!battleCharacter)
    {
        _ASSERT(0);
        return;
    }

    if (0 == type)
    {
        auto& manager = character.GetPropertyManager();
        manager.AddHealthValue(model.HealthValue);
        manager.AddManaValue(model.ManaValue);
    }
    else
    {
        action.CustomApplyRestorerResult(character, model, type);
    }

    //model.Releaser->OnRestorerActionFinished(model);
    (*battleCharacter)->GetActionInterceptor().AfterRestorerAction(action, model, type);
}

void FBattleSystem::ApplyStatusResult(const ISingleAction& action, ICharacterBattleDelegate& character,
    const FBaseStatusModel& model, int32 type)
{
    auto battleCharacter = FindCharacter(&character);
    if (!battleCharacter)
    {
        _ASSERT(0);
        return;
    }

    if (0 == type)
    {
        auto& manager = (*battleCharacter)->GetTempStatusManager();
        manager.AddTemporaryStatus(model.StatusType, model.TempStatusOpWrapper);
    }
    else
    {
        action.CustomApplyStatusResult(character, model, type);
    }

    //model.Releaser->OnStatusActionFinished(model);
    (*battleCharacter)->GetActionInterceptor().AfterStatusAction(action, model, type);
}

void FBattleSystem::DoAttackAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FAttackCallback cb)
{

}

void FBattleSystem::DoRestorerAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FRestorerCallback cb)
{
}

void FBattleSystem::DoStatusAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FStatusCallback cb)
{
}

TSharedRef<FBattleCharacter>* FBattleSystem::FindCharacter(const ICharacterBattleDelegate* del)
{
    for (auto& character : Characters)
    {
        if (del == &character->GetCharacterDelegate())
        {
            return &character;
        }
    }

    return nullptr;
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
