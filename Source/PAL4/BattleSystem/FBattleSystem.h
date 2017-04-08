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

    // ս����ʼ�¼�
    FBattleBeginEvent& OnBattleBegin() { return BattleBeginEvent; }
    // ս�������¼�
    FBattleFinishedEvent& OnBattleFinished() { return BattleFinishedEvent; }
    // ���Ｔ���ж�
    FCharacterWillActEvent& OnCharacterWillAct() { return CharacterWillActEvent; }
    // ��������ж�
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
     * ��ʼ����ս��
     */
    void Run();

    bool BattleIsOver() const;
    /**
     * ��ȡս�����������һ���Ƿ�ʤ����
     * @warning �˷�������ս������(@see BattleIsOver)��ž�����ȷ�ķ���ֵ�����ս��δ����������ֵ��δ֪�ġ�
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
    // �洢ÿ����ս����ĻغϹ�����ʵ������ֱ�Ӵ������Ǵ洢����ָ�룬ԭ��������б���ܻ������Ӳ�����
    // ��ô���п��ܻᵼ���б�洢�ڴ��ط��䣬���ָ������Ԫ��ʵ����ָ�����ң���FCharacterRoundManager��
    // ����õ������thisָ���ֵ����
    TArray<TSharedRef<FCharacterRoundManager>> RoundManagers;

    // ���һ�γ��ֵ���
    ICharacterBattleDelegate *CharacterActLast;
};
