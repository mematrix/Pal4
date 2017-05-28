// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <algorithm>

#include "Util/EventUtil.h"

#include "FCombatSystem.h"
#include "CombatDelegate/Character/ICharacterPropertyManager.h"
#include "Character/FCombatCharacter.h"
#include "ActionCore/Model/FBaseAttackModel.h"
#include "ActionCore/Model/FBaseRestorerModel.h"
#include "ActionCore/Model/FBaseStatusModel.h"
#include "ActionCore/ISingleAction.h"


class PAL4_API RoundDispatcherRaii
{
    IRoundDispatcher& Dispatcher;

public:
    explicit RoundDispatcherRaii(IRoundDispatcher& dispatcher) : Dispatcher(dispatcher) { }
    ~RoundDispatcherRaii() { Dispatcher.OnBattleFinished(); }
};


FCombatSystem::FCombatSystem(const TArray<TSharedRef<ICharacterDelegate>>& characters,
    const TSharedRef<IRoundDispatcher>& dispatcher) :
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
        Characters.Emplace(MakeShared<FCombatCharacter>(characters[i]));
    }

    Dispatcher->Init(characters);
}

FCombatSystem::~FCombatSystem()
{
}

void FCombatSystem::AddCharacter(const TSharedRef<ICharacterDelegate>& characterDelegate)
{
    Characters.Add(MakeShared<FCombatCharacter>(characterDelegate));
    Dispatcher->AddCharacter(characterDelegate);
}

void FCombatSystem::Run()
{
    InvokeEvent(BattleBeginEvent, *this);

    // 不应该出现这种情况
    _ASSERT(!BattleIsOver());

    {
        RoundDispatcherRaii dispatcherRaii(Dispatcher.Get());
        Dispatcher->OnBattleBegin();

        FCombatCharacter* characterActLast = nullptr;
        while (!BattleIsOver())
        {
            ICharacterDelegate& character = Dispatcher->MoveToNext();
            characterActLast = static_cast<FCombatCharacter*>(character.GetContext());

            InvokeEvent(CharacterWillActEvent, *this, character);

            auto& roundManager = characterActLast->GetRoundManager();
            // TODO: 需要判断是否跳过回合
            roundManager.DoRoundAction();

            InvokeEvent(CharacterFinishActEvent, *this, character);
        }

        CharacterActLast = characterActLast;
    }

    InvokeEvent(BattleFinishedEvent, *this);
}

void FCombatSystem::ApplyAttackResult(const ISingleAction& action, FCombatCharacter& character,
    const FBaseAttackModel& model, int32 type)
{
    if (static_cast<uint32>(type) <= 3)
    {
        auto& propertyManager = character.GetPropertyManager();
        propertyManager.AddHealthValue(-model.TotalValue);
    }
    else
    {
        action.CustomApplyAttackResult(character.GetCharacterDelegate(), model, type);
    }

    action.OnAttackFinished(character.GetCharacterDelegate(), model, type);
    character.GetActionInterceptor().AfterAttackAction(action, model, type);
}

void FCombatSystem::ApplyRestorerResult(const ISingleAction& action, FCombatCharacter& character,
    const FBaseRestorerModel& model, int32 type)
{
    if (0 == type)
    {
        auto& manager = character.GetPropertyManager();
        manager.AddHealthValue(model.HealthValue);
        manager.AddManaValue(model.ManaValue);
    }
    else
    {
        action.CustomApplyRestorerResult(character.GetCharacterDelegate(), model, type);
    }

    action.OnRestorerFinished(character.GetCharacterDelegate(), model, type);
    character.GetActionInterceptor().AfterRestorerAction(action, model, type);
}

void FCombatSystem::ApplyStatusResult(const ISingleAction& action, FCombatCharacter& character,
    const FBaseStatusModel& model, int32 type)
{
    if (0 == type)
    {
        auto& manager = character.GetTempStatusManager();
        manager.AddTemporaryStatus(model.StatusType, model.TempStatusOpWrapper);
    }
    else
    {
        action.CustomApplyStatusResult(character.GetCharacterDelegate(), model, type);
    }

    action.OnStatusFinished(character.GetCharacterDelegate(), model, type);
    character.GetActionInterceptor().AfterStatusAction(action, model, type);
}

void FCombatSystem::DoAttackAction(const ISingleAction& action, ICharacterDelegate& character, int32 type, FAttackCallback cb) const
{
    _ASSERT(IsCharacterExist(character));

    auto& battleCharacter = static_cast<FCombatCharacter&>(*character.GetContext());
    auto model = battleCharacter.GetActionInterceptor().AfterComputeAttackResult(action, action.ComputeAttackResult(character, type), type);

    if (cb)
    {
        cb(action, character, model.Get(), type);
    }

    ApplyAttackResult(action, battleCharacter, model.Get(), type);
}

void FCombatSystem::DoRestorerAction(const ISingleAction& action, ICharacterDelegate& character, int32 type, FRestorerCallback cb) const
{
    _ASSERT(IsCharacterExist(character));

    auto& battleCharacter = static_cast<FCombatCharacter&>(*character.GetContext());
    auto model = battleCharacter.GetActionInterceptor().AfterComputeRestorerResult(action, action.ComputeRestorerResult(character, type), type);

    if (cb)
    {
        cb(action, character, model.Get(), type);
    }

    ApplyRestorerResult(action, battleCharacter, model.Get(), type);
}

void FCombatSystem::DoStatusAction(const ISingleAction& action, ICharacterDelegate& character, int32 type, FStatusCallback cb) const
{
    _ASSERT(IsCharacterExist(character));

    auto& battleCharacter = static_cast<FCombatCharacter&>(*character.GetContext());
    auto model = battleCharacter.GetActionInterceptor().AfterComputeStatusResult(action, action.ComputeStatusResult(character, type), type);

    if (cb)
    {
        cb(action, character, model.Get(), type);
    }

    ApplyStatusResult(action, battleCharacter, model.Get(), type);
}

bool FCombatSystem::IsCharacterExist(const ICharacterDelegate& characterDelegate) const
{
    if (!characterDelegate.GetContext())
    {
        return false;
    }

    for (auto& character : Characters)
    {
        if (characterDelegate.GetContext() == character.operator->())
        {
            return true;
        }
    }

    return false;
}

int32 FCombatSystem::StatAliveStatus() const
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

bool FCombatSystem::BattleIsOver() const
{
    return StatAliveStatus() != 3;
}

bool FCombatSystem::IsPlayerWinned() const
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
