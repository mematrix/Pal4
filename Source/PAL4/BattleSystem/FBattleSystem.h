// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Array.h>
#include <SharedPointer.h>

#include "FCharacterRoundManager.h"
#include "CharacterBridge/ICharacterBattleDelegate.h"
#include "RoundDispatcher/ICharacterRoundDispatcher.h"

/**
 * 
 */
class PAL4_API FBattleSystem
{
public:
    DECLARE_EVENT_OneParam(FBattleSystem, FBattleBeginEvent, const FBattleSystem&)
    DECLARE_EVENT_OneParam(FBattleSystem, FBattleFinishedEvent, const FBattleSystem&)
    DECLARE_EVENT_TwoParams(FBattleSystem, FCharacterWillActEvent, const FBattleSystem&, const ICharacterBattleDelegate&)
    DECLARE_EVENT_TwoParams(FBattleSystem, FCharacterFinishActEvent, const FBattleSystem&, const ICharacterBattleDelegate&)

public:
    FBattleSystem(const TArray<TSharedRef<ICharacterBattleDelegate>>&, const TSharedRef<ICharacterRoundDispatcher>&);
    FBattleSystem(const FBattleSystem&) = delete;
	~FBattleSystem();

    FBattleSystem& operator=(const FBattleSystem&) = delete;

    // 战斗开始事件
    FBattleBeginEvent& OnBattleBegin() { return BattleBeginEvent; }
    // 战斗结束事件
    FBattleFinishedEvent& OnBattleFinished() { return BattleFinishedEvent; }
    // 人物即将行动
    FCharacterWillActEvent& OnCharacterWillAct() { return CharacterWillActEvent; }
    // 人物结束行动
    FCharacterFinishActEvent& OnCharacterFinishAct() { return CharacterFinishActEvent; }

    // TArray<TSharedRef<ICharacterBattleDelegate>>& GetCharacters() { return Characters; }
    const TArray<TSharedRef<ICharacterBattleDelegate>>& GetCharacters() const { return Characters; }

    void AddCharacter(const TSharedRef<ICharacterBattleDelegate>& character);

    const TSharedRef<ICharacterRoundDispatcher>& GetDispatcher() const { return Dispatcher; }

    void SetDispatcher(const TSharedRef<ICharacterRoundDispatcher>& dispatcher)
    {
        Dispatcher = dispatcher;
    }

    /**
     * 开始进入战斗
     */
    void Run();

    bool BattleIsOver() const;
    /**
     * 获取战斗结束后玩家一方是否胜利。
     * @warning 此方法仅在战斗结束(@see BattleIsOver)后才具有正确的返回值，如果战斗未结束，返回值是未知的。
     */
    bool IsPlayerWinned() const;

private:
    bool IsPlayerWinned(TSharedRef<ICharacterBattleDelegate>&) const;

private:
    FBattleBeginEvent BattleBeginEvent;
    FBattleFinishedEvent BattleFinishedEvent;
    FCharacterWillActEvent CharacterWillActEvent;
    FCharacterFinishActEvent CharacterFinishActEvent;

    TArray<TSharedRef<ICharacterBattleDelegate>> Characters;
    TSharedRef<ICharacterRoundDispatcher> Dispatcher;
    // 存储每个参战人物的回合管理器实例。不直接存对象而是存储智能指针，原因是这个列表可能会有增加操作，
    // 那么就有可能会导致列表存储内存重分配，造成指向其中元素实例的指针悬挂（在FCharacterRoundManager里
    // 面会用到自身的this指针的值。）
    TArray<TSharedRef<FCharacterRoundManager>> RoundManagers;

    // 最后一次出手的人
    ICharacterBattleDelegate *CharacterActLast;
};
