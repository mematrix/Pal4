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

void FBattleSystem::SetStatusResultCallback(const FStatusFunc& func)
{
    CustomStatusFunc = func;
}

void FBattleSystem::ApplyStatusResult(const ActionResultModel<FBaseStatusModel>& model)
{
    if (0 == model.Type)
    {
        auto battleCharacter = FindCharacter(model.Target);
        if (!battleCharacter)
        {
            _ASSERT(0);
            return;
        }

        auto& manager = (*battleCharacter)->GetTempStatusManager();
        manager.AddTemporaryStatus(model.ActionModel->StatusType, model.ActionModel->TempStatusOpWrapper);
    }
    else
    {
        if (CustomStatusFunc)
        {
            CustomStatusFunc(model);
        }
    }
}

void FBattleSystem::SetAttackResultCallback(const FAttackFunc& func)
{
    CustomAttackFunc = func;
}

void FBattleSystem::ApplyAttackResult(const ActionResultModel<FBaseAttackModel>& model)
{
    TSharedRef<FBattleCharacter>* battleCharacter = nullptr;
    if (static_cast<uint32>(model.Type) <= 3)
    {
        battleCharacter = FindCharacter(model.Target);
        if (!battleCharacter)
        {
            _ASSERT(0);
            return;
        }
    }

    switch (model.Type)
    {
    case 0:
    {
        auto normalModel = static_cast<const FNormalAttackModel*>(model.ActionModel);
        auto& propertyManager = model.Target->GetPropertyManager();
        
        break;
    }

    case 1:
    {
        auto maginModel = static_cast<const FMagicAttackModel*>(model.ActionModel);
        
        break;
    }

    case 2:
    {
        auto skillModel = static_cast<const FSkillAttackModel*>(model.ActionModel);
        //
        break;
    }

    case 3:
    {
        auto propModel = static_cast<const FPropAttackModel*>(model.ActionModel);
        //
        break;
    }

    default:
    {
        if (CustomAttackFunc)
        {
            CustomAttackFunc(model);
        }
        break;
    }
    }
}

void FBattleSystem::SetRestorerResultCallback(const FRestorerFunc& func)
{
    CustomRestorerFunc = func;
}

void FBattleSystem::ApplyRestorerResult(const ActionResultModel<FBaseRestorerModel>& model)
{
    if (0 == model.Type)
    {
        //
    }
    else
    {
        if (CustomRestorerFunc)
        {
            CustomRestorerFunc(model);
        }
    }
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
