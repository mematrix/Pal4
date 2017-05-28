// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include <Array.h>
#include <SharedPointer.h>

#include "Combat/Interface/Character/ICharacterCombatDelegate.h"
#include "Combat/Interface/Round/ICharacterRoundDispatcher.h"

class FCombatCharacter;
class ISingleAction;
struct FBaseStatusModel;
struct FBaseAttackModel;
struct FBaseRestorerModel;


/**
 *
 */
class PAL4_API FCombatSystem
{
public:
    typedef std::function<void(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseAttackModel&, int32)> FAttackCallback;
    typedef std::function<void(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseRestorerModel&, int32)> FRestorerCallback;
    typedef std::function<void(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseStatusModel&, int32)> FStatusCallback;

    DECLARE_EVENT_OneParam(FCombatSystem, FBattleBeginEvent, const FCombatSystem&)
    DECLARE_EVENT_OneParam(FCombatSystem, FBattleFinishedEvent, const FCombatSystem&)
    DECLARE_EVENT_TwoParams(FCombatSystem, FCharacterWillActEvent, const FCombatSystem&, const ICharacterCombatDelegate&)
    DECLARE_EVENT_TwoParams(FCombatSystem, FCharacterFinishActEvent, const FCombatSystem&, const ICharacterCombatDelegate&)

public:
    FCombatSystem(const TArray<TSharedRef<ICharacterCombatDelegate>>&, const TSharedRef<ICharacterRoundDispatcher>&);
    FCombatSystem(const FCombatSystem&) = delete;
    ~FCombatSystem();

    FCombatSystem& operator=(const FCombatSystem&) = delete;

    // ս����ʼ�¼�
    FBattleBeginEvent& OnBattleBegin() const { return BattleBeginEvent; }
    // ս�������¼�
    FBattleFinishedEvent& OnBattleFinished() const { return BattleFinishedEvent; }
    // ���Ｔ���ж�
    FCharacterWillActEvent& OnCharacterWillAct() const { return CharacterWillActEvent; }
    // ��������ж�
    FCharacterFinishActEvent& OnCharacterFinishAct() const { return CharacterFinishActEvent; }

    // TArray<TSharedRef<ICharacterCombatDelegate>>& GetCharacters() { return Characters; }
    const TArray<TSharedRef<FCombatCharacter>>& GetCharacters() const { return Characters; }

    void AddCharacter(const TSharedRef<ICharacterCombatDelegate>&);

    const TSharedRef<ICharacterRoundDispatcher>& GetDispatcher() const { return Dispatcher; }

    /**
     * ��ʼ����ս��
     */
    void Run();

private:
    /**
     * Ӧ�ù����Զ��������
     * ��������ͬ@code FCombatSystem::DoAttackAction \endcode
     */
    static void ApplyAttackResult(const ISingleAction&, FCombatCharacter&, const FBaseAttackModel&, int32);

    /**
     * Ӧ�ûָ��Զ��������
     * ��������ͬ@code FCombatSystem::DoRestorerAction \endcode
     */
    static void ApplyRestorerResult(const ISingleAction&, FCombatCharacter&, const FBaseRestorerModel&, int32);

    /**
     * Ӧ��״̬�Զ��������
     * ��������ͬ@code FCombatSystem::DoStatusAction \endcode
     */
    static void ApplyStatusResult(const ISingleAction&, FCombatCharacter&, const FBaseStatusModel&, int32);

public:
    /**
     * ִ�й����Զ�������������0~3�Ѿ���Ĭ����Ϊ����������ֵ���ص�@code ISingleAction::CustomApplyAttackResult \endcode
     * �������ṩһ���ص��������ڼ�����˺�ֵ֮�󡢶�Ŀ���ɫִ���˺�����֮ǰ���ã����ڸ���UI
     * @param action ��������
     * @param character ��������
     * @param type ��������
     * @param cb ���ڸ���UI�Ļص�����
     */
    void DoAttackAction(const ISingleAction& action, ICharacterCombatDelegate& character, int32 type, FAttackCallback cb) const;

    /**
     * ִ�лָ��Զ���������0����Ĭ����Ϊ����������ֵ���ص�@code ISingleAction::CustomApplyRestorerResult \endcode
     * �������ṩһ���ص��������ڼ�����˺�ֵ֮�󡢶�Ŀ���ɫִ���˺�����֮ǰ���ã����ڸ���UI
     * @param action �ָ�����
     * @param character �ָ�Ŀ��
     * @param type �ָ�����
     * @param cb ���ڸ���UI�Ļص�����
     */
    void DoRestorerAction(const ISingleAction& action, ICharacterCombatDelegate& character, int32 type, FRestorerCallback cb) const;

    /**
     * ִ��״̬�Զ���������0�Ѿ���Ĭ����Ϊ����������ֵ���ص�@code ISingleAction::CustomApplyStatusResult \endcode
     * �������ṩһ���ص��������ڼ�����˺�ֵ֮�󡢶�Ŀ���ɫִ���˺�����֮ǰ���ã����ڸ���UI
     * @param action ״̬����
     * @param character Ӧ��Ŀ��
     * @param type ����
     * @param cb ���ڸ���UI�Ļص�����
     */
    void DoStatusAction(const ISingleAction& action, ICharacterCombatDelegate& character, int32 type, FStatusCallback cb) const;

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
    bool IsCharacterExist(const ICharacterCombatDelegate&) const;

    bool BattleIsOver() const;
    /**
     * ��ȡս�����������һ���Ƿ�ʤ����
     * @warning �˷�������ս������(@see BattleIsOver)��ž�����ȷ�ķ���ֵ�����ս��δ����������ֵ��δ֪�ġ�
     */
    bool IsPlayerWinned() const;

private:
    mutable FBattleBeginEvent BattleBeginEvent;
    mutable FBattleFinishedEvent BattleFinishedEvent;
    mutable FCharacterWillActEvent CharacterWillActEvent;
    mutable FCharacterFinishActEvent CharacterFinishActEvent;

    TArray<TSharedRef<FCombatCharacter>> Characters;
    TSharedRef<ICharacterRoundDispatcher> Dispatcher;
    // �洢ÿ����ս����ĻغϹ�����ʵ������ֱ�Ӵ������Ǵ洢����ָ�룬ԭ��������б���ܻ������Ӳ�����
    // ��ô���п��ܻᵼ���б�洢�ڴ��ط��䣬���ָ������Ԫ��ʵ����ָ�����ң���FCharacterRoundManager��
    // ����õ������thisָ���ֵ����
    // TArray<TSharedRef<FRoundManager>> RoundManagers;

    // ���һ�γ��ֵ���
    FCombatCharacter *CharacterActLast;
};
