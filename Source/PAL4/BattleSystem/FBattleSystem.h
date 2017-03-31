// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Array.h>
#include <SharedPointer.h>

#include "IBattleStatus.h"
#include "ICharacterRoundDispatcher.h"
#include "FCharacterRoundManager.h"

/**
 * 
 */
class PAL4_API FBattleSystem
{
public:
    DECLARE_EVENT_OneParam(FBattleSystem, FBattleBeginEvent, const FBattleSystem&)
    DECLARE_EVENT_OneParam(FBattleSystem, FBattleFinishedEvent, const FBattleSystem&)
    DECLARE_EVENT_TwoParams(FBattleSystem, FCharacterWillActEvent, const FBattleSystem&, const IBattleStatus&)
    DECLARE_EVENT_TwoParams(FBattleSystem, FCharacterFinishActEvent, const FBattleSystem&, const IBattleStatus&)

public:
    FBattleSystem(TArray<TSharedRef<IBattleStatus>>&, TSharedRef<ICharacterRoundDispatcher>&);
    FBattleSystem(const FBattleSystem&) = delete;
	~FBattleSystem();

    FBattleSystem& operator=(const FBattleSystem&) = delete;

    // ս����ʼ�¼�
    FBattleBeginEvent& OnBattleBegin() { return BattleBeginEvent; }
    // ս�������¼�
    FBattleFinishedEvent& OnBattleFinished() { return BattleFinishedEvent; }
    FCharacterWillActEvent& OnCharacterWillAct() { return CharacterWillActEvent; }
    FCharacterFinishActEvent& OnCharacterFinishAct() { return CharacterFinishActEvent; }

    // TArray<TSharedRef<IBattleStatus>>& GetCharacters() { return Characters; }
    const TArray<TSharedRef<IBattleStatus>>& GetCharacters() const { return Characters; }

    void AddCharacter(const TSharedRef<IBattleStatus>& character);

    const TSharedRef<ICharacterRoundDispatcher>& GetDispatcher() const { return Dispatcher; }

    void SetDispatcher(const TSharedRef<ICharacterRoundDispatcher>& dispatcher)
    {
        Dispatcher = dispatcher;
    }

    /**
     * ��ʼ����ս��
     */
    void Run();

    bool BattleIsOver() const;
    /*
     * ��ȡս�����������һ���Ƿ�ʤ����
     * @warning �˷�������ս������(@see BattleIsOver)��ž�����ȷ�ķ���ֵ�����ս��δ����������ֵ��δ֪�ġ�
     */
    bool IsPlayerWinned() const;

private:
    bool IsPlayerWinned(TSharedRef<IBattleStatus>&) const;

private:
    FBattleBeginEvent BattleBeginEvent;
    FBattleFinishedEvent BattleFinishedEvent;
    FCharacterWillActEvent CharacterWillActEvent;
    FCharacterFinishActEvent CharacterFinishActEvent;

    TArray<TSharedRef<IBattleStatus>> Characters;
    TSharedRef<ICharacterRoundDispatcher> Dispatcher;
    // �洢ÿ����ս����ĻغϹ�����ʵ������ֱ�Ӵ������Ǵ洢����ָ�룬ԭ��������б���ܻ������Ӳ�����
    // ��ô���п��ܻᵼ���б�洢�ڴ��ط��䣬���ָ������Ԫ��ʵ����ָ�����ң���FCharacterRoundManager��
    // ����õ������thisָ���ֵ����
    TArray<TSharedRef<FCharacterRoundManager>> RoundManagers;

    // ���һ�γ��ֵ���
    IBattleStatus *CharacterActLast;
};
