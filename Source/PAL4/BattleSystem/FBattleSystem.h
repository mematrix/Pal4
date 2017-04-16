// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include <Array.h>
#include <SharedPointer.h>

#include "CharacterBridge/ICharacterBattleDelegate.h"
#include "RoundDispatcher/ICharacterRoundDispatcher.h"

class FBattleCharacter;
struct FBaseStatusModel;
struct FBaseAttackModel;
struct FBaseRestorerModel;


typedef std::function<void(const ActionResultModel<FBaseStatusModel>&)> FStatusFunc;
typedef std::function<void(const ActionResultModel<FBaseAttackModel>&)> FAttackFunc;
typedef std::function<void(const ActionResultModel<FBaseRestorerModel>&)> FRestorerFunc;

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
    const TArray<TSharedRef<FBattleCharacter>>& GetCharacters() const { return Characters; }

    void AddCharacter(const TSharedRef<ICharacterBattleDelegate>&);

    const TSharedRef<ICharacterRoundDispatcher>& GetDispatcher() const { return Dispatcher; }

    /**
     * ��ʼ����ս��
     */
    void Run();

    void SetStatusResultCallback(const FStatusFunc&);

    /**
     * Ӧ��״̬�Զ������������0�Ѿ���Ĭ����Ϊ����������ֵ�������Զ��崦������Ҫ�����Զ��崦������
     * �μ�@code SetStatusResultCallback(const std::function<...>&) \endcode ��
     * @param model ״̬����ģ���ࡣ@code model.type \endcode Ϊ0��Ӧ��Ĭ����Ϊ���������Ĭ�ϵķ�ʽ����״̬�߼�
     */
    void ApplyStatusResult(const ActionResultModel<FBaseStatusModel>& model);

    void SetAttackResultCallback(const FAttackFunc&);

    /**
     * Ӧ�ù����Զ����������������0~3�Ѿ���Ĭ����Ϊ����������ֵ�������Զ��崦������Ҫ�����Զ��崦������
     * �μ�@code SetAttackResultCallback(const std::function<...>&) \endcode ��
     * @param model ��������ģ���ࡣ@code model.type \endcode Ϊ0,1,2,3��Ӧ��ͨ�������������������ܹ�������Ʒ����
     */
    void ApplyAttackResult(const ActionResultModel<FBaseAttackModel>& model);

    void SetRestorerResultCallback(const FRestorerFunc&);

    /**
     * Ӧ�ûָ��Զ������������0����Ĭ����Ϊ����������ֵ�������Զ��崦������Ҫ�����Զ��崦������
     * �μ�@code SetRestorerResultCallback(const std::function<...>&) \endcode ��
     * @param model �ָ�����ģ���ࡣ@code model.type \endcode Ϊ0��Ӧ��Ĭ����Ϊ���������Ĭ�ϵķ�ʽ����ָ��߼�
     */
    void ApplyRestorerResult(const ActionResultModel<FBaseRestorerModel>& model);

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
    TSharedRef<FBattleCharacter>* FindCharacter(const ICharacterBattleDelegate*);

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

    FStatusFunc CustomStatusFunc;
    FAttackFunc CustomAttackFunc;
    FRestorerFunc CustomRestorerFunc;

    // ���һ�γ��ֵ���
    FBattleCharacter *CharacterActLast;
};
