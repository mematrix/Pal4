// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include <Array.h>
#include <SharedPointer.h>

#include "CombatDelegate/Character/ICharacterBattleDelegate.h"
#include "CombatDelegate/RoundDispatcher/ICharacterRoundDispatcher.h"

class FBattleCharacter;
class ISingleAction;
struct FBaseStatusModel;
struct FBaseAttackModel;
struct FBaseRestorerModel;


/**
 *
 */
class PAL4_API FBattleSystem
{
public:
    typedef std::function<void(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseAttackModel&, int32)> FAttackCallback;
    typedef std::function<void(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseRestorerModel&, int32)> FRestorerCallback;
    typedef std::function<void(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseStatusModel&, int32)> FStatusCallback;

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
    const TArray<TSharedRef<FBattleCharacter>>& GetCharacters() const { return Characters; }

    void AddCharacter(const TSharedRef<ICharacterBattleDelegate>&);

    const TSharedRef<ICharacterRoundDispatcher>& GetDispatcher() const { return Dispatcher; }

    /**
     * ��ʼ����ս��
     */
    void Run();

private:
    /**
     * Ӧ�ù����Զ��������
     * ��������ͬ@code FBattleSystem::DoAttackAction \endcode
     */
    static void ApplyAttackResult(const ISingleAction&, FBattleCharacter&, const FBaseAttackModel&, int32);

    /**
     * Ӧ�ûָ��Զ��������
     * ��������ͬ@code FBattleSystem::DoRestorerAction \endcode
     */
    static void ApplyRestorerResult(const ISingleAction&, FBattleCharacter&, const FBaseRestorerModel&, int32);

    /**
     * Ӧ��״̬�Զ��������
     * ��������ͬ@code FBattleSystem::DoStatusAction \endcode
     */
    static void ApplyStatusResult(const ISingleAction&, FBattleCharacter&, const FBaseStatusModel&, int32);

public:
    /**
     * ִ�й����Զ�������������0~3�Ѿ���Ĭ����Ϊ����������ֵ���ص�@code ISingleAction::CustomApplyAttackResult \endcode
     * �������ṩһ���ص��������ڼ�����˺�ֵ֮�󡢶�Ŀ���ɫִ���˺�����֮ǰ���ã����ڸ���UI
     * @param action ��������
     * @param character ��������
     * @param type ��������
     * @param cb ���ڸ���UI�Ļص�����
     */
    void DoAttackAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FAttackCallback cb) const;

    /**
     * ִ�лָ��Զ���������0����Ĭ����Ϊ����������ֵ���ص�@code ISingleAction::CustomApplyRestorerResult \endcode
     * �������ṩһ���ص��������ڼ�����˺�ֵ֮�󡢶�Ŀ���ɫִ���˺�����֮ǰ���ã����ڸ���UI
     * @param action �ָ�����
     * @param character �ָ�Ŀ��
     * @param type �ָ�����
     * @param cb ���ڸ���UI�Ļص�����
     */
    void DoRestorerAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FRestorerCallback cb) const;

    /**
     * ִ��״̬�Զ���������0�Ѿ���Ĭ����Ϊ����������ֵ���ص�@code ISingleAction::CustomApplyStatusResult \endcode
     * �������ṩһ���ص��������ڼ�����˺�ֵ֮�󡢶�Ŀ���ɫִ���˺�����֮ǰ���ã����ڸ���UI
     * @param action ״̬����
     * @param character Ӧ��Ŀ��
     * @param type ����
     * @param cb ���ڸ���UI�Ļص�����
     */
    void DoStatusAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FStatusCallback cb) const;

private:
    /**
     * ����ֵ��һ��flag����0λ��ʶ���һ��״̬��Ϊ1��ʾ����н�ɫ��Ϊ0��ʾ���һ���޽�ɫ����1λͬ��
     * ��ʶAIһ��״̬��
     *
     * ö��ֵ���£�
     * 0x00: û���κ�һ���д��Ľ�ɫ
     * 0x01: ֻ�����һ���д��Ľ�ɫ
     * 0x02: ֻ��AIһ���д���ɫ
     * 0x03: ˫�����д���ɫ
     */
    int32 StatAliveStatus() const;

public:
    bool IsCharacterExist(const ICharacterBattleDelegate&) const;

    bool BattleIsOver() const;
    /**
     * ��ȡս�����������һ���Ƿ�ʤ����
     * @warning �˷�������ս������(@see BattleIsOver)��ž�����ȷ�ķ���ֵ�����ս��δ����������ֵ��δ֪�ġ�
     */
    bool IsPlayerWinned() const;

private:
    FBattleBeginEvent BattleBeginEvent;
    FBattleFinishedEvent BattleFinishedEvent;
    FCharacterWillActEvent CharacterWillActEvent;
    FCharacterFinishActEvent CharacterFinishActEvent;

    TArray<TSharedRef<FBattleCharacter>> Characters;
    TSharedRef<ICharacterRoundDispatcher> Dispatcher;
    // �洢ÿ����ս����ĻغϹ�����ʵ������ֱ�Ӵ������Ǵ洢����ָ�룬ԭ��������б���ܻ������Ӳ�����
    // ��ô���п��ܻᵼ���б�洢�ڴ��ط��䣬���ָ������Ԫ��ʵ����ָ�����ң���FCharacterRoundManager��
    // ����õ������thisָ���ֵ����
    // TArray<TSharedRef<FCharacterRoundManager>> RoundManagers;

    // ���һ�γ��ֵ���
    FBattleCharacter *CharacterActLast;
};
