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

    // 战斗开始事件
    FBattleBeginEvent& OnBattleBegin() { return BattleBeginEvent; }
    // 战斗结束事件
    FBattleFinishedEvent& OnBattleFinished() { return BattleFinishedEvent; }
    // 人物即将行动
    FCharacterWillActEvent& OnCharacterWillAct() { return CharacterWillActEvent; }
    // 人物结束行动
    FCharacterFinishActEvent& OnCharacterFinishAct() { return CharacterFinishActEvent; }

    // TArray<TSharedRef<ICharacterBattleDelegate>>& GetCharacters() { return Characters; }
    const TArray<TSharedRef<FBattleCharacter>>& GetCharacters() const { return Characters; }

    void AddCharacter(const TSharedRef<ICharacterBattleDelegate>&);

    const TSharedRef<ICharacterRoundDispatcher>& GetDispatcher() const { return Dispatcher; }

    /**
     * 开始进入战斗
     */
    void Run();

private:
    /**
     * 应用攻击性动作结果。
     * 参数含义同@code FBattleSystem::DoAttackAction \endcode
     */
    static void ApplyAttackResult(const ISingleAction&, FBattleCharacter&, const FBaseAttackModel&, int32);

    /**
     * 应用恢复性动作结果。
     * 参数含义同@code FBattleSystem::DoRestorerAction \endcode
     */
    static void ApplyRestorerResult(const ISingleAction&, FBattleCharacter&, const FBaseRestorerModel&, int32);

    /**
     * 应用状态性动作结果。
     * 参数含义同@code FBattleSystem::DoStatusAction \endcode
     */
    static void ApplyStatusResult(const ISingleAction&, FBattleCharacter&, const FBaseStatusModel&, int32);

public:
    /**
     * 执行攻击性动作。攻击类型0~3已经有默认行为，传入其它值将回调@code ISingleAction::CustomApplyAttackResult \endcode
     * 方法。提供一个回调函数，在计算出伤害值之后、对目标角色执行伤害结算之前调用，用于更新UI
     * @param action 攻击动作
     * @param character 被攻击者
     * @param type 攻击类型
     * @param cb 用于更新UI的回调函数
     */
    void DoAttackAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FAttackCallback cb) const;

    /**
     * 执行恢复性动作。类型0已有默认行为，传入其他值将回调@code ISingleAction::CustomApplyRestorerResult \endcode
     * 方法。提供一个回调函数，在计算出伤害值之后、对目标角色执行伤害结算之前调用，用于更新UI
     * @param action 恢复动作
     * @param character 恢复目标
     * @param type 恢复类型
     * @param cb 用于更新UI的回调函数
     */
    void DoRestorerAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FRestorerCallback cb) const;

    /**
     * 执行状态性动作。类型0已经有默认行为，传入其它值将回调@code ISingleAction::CustomApplyStatusResult \endcode
     * 方法。提供一个回调函数，在计算出伤害值之后、对目标角色执行伤害结算之前调用，用于更新UI
     * @param action 状态动作
     * @param character 应用目标
     * @param type 类型
     * @param cb 用于更新UI的回调函数
     */
    void DoStatusAction(const ISingleAction& action, ICharacterBattleDelegate& character, int32 type, FStatusCallback cb) const;

private:
    /**
     * 返回值是一个flag。第0位标识玩家一方状态，为1表示玩家有角色存活，为0表示玩家一方无角色存活；第1位同理，
     * 标识AI一方状态。
     *
     * 枚举值如下：
     * 0x00: 没有任何一方有存活的角色
     * 0x01: 只有玩家一方有存活的角色
     * 0x02: 只有AI一方有存活角色
     * 0x03: 双方都有存活角色
     */
    int32 StatAliveStatus() const;

public:
    bool IsCharacterExist(const ICharacterBattleDelegate&) const;

    bool BattleIsOver() const;
    /**
     * 获取战斗结束后玩家一方是否胜利。
     * @warning 此方法仅在战斗结束(@see BattleIsOver)后才具有正确的返回值，如果战斗未结束，返回值是未知的。
     */
    bool IsPlayerWinned() const;

private:
    FBattleBeginEvent BattleBeginEvent;
    FBattleFinishedEvent BattleFinishedEvent;
    FCharacterWillActEvent CharacterWillActEvent;
    FCharacterFinishActEvent CharacterFinishActEvent;

    TArray<TSharedRef<FBattleCharacter>> Characters;
    TSharedRef<ICharacterRoundDispatcher> Dispatcher;
    // 存储每个参战人物的回合管理器实例。不直接存对象而是存储智能指针，原因是这个列表可能会有增加操作，
    // 那么就有可能会导致列表存储内存重分配，造成指向其中元素实例的指针悬挂（在FCharacterRoundManager里
    // 面会用到自身的this指针的值。）
    // TArray<TSharedRef<FCharacterRoundManager>> RoundManagers;

    // 最后一次出手的人
    FBattleCharacter *CharacterActLast;
};
