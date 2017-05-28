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

    // 战斗开始事件
    FBattleBeginEvent& OnBattleBegin() const { return BattleBeginEvent; }
    // 战斗结束事件
    FBattleFinishedEvent& OnBattleFinished() const { return BattleFinishedEvent; }
    // 人物即将行动
    FCharacterWillActEvent& OnCharacterWillAct() const { return CharacterWillActEvent; }
    // 人物结束行动
    FCharacterFinishActEvent& OnCharacterFinishAct() const { return CharacterFinishActEvent; }

    // TArray<TSharedRef<ICharacterCombatDelegate>>& GetCharacters() { return Characters; }
    const TArray<TSharedRef<FCombatCharacter>>& GetCharacters() const { return Characters; }

    void AddCharacter(const TSharedRef<ICharacterCombatDelegate>&);

    const TSharedRef<ICharacterRoundDispatcher>& GetDispatcher() const { return Dispatcher; }

    /**
     * 开始进入战斗
     */
    void Run();

private:
    /**
     * 应用攻击性动作结果。
     * 参数含义同@code FCombatSystem::DoAttackAction \endcode
     */
    static void ApplyAttackResult(const ISingleAction&, FCombatCharacter&, const FBaseAttackModel&, int32);

    /**
     * 应用恢复性动作结果。
     * 参数含义同@code FCombatSystem::DoRestorerAction \endcode
     */
    static void ApplyRestorerResult(const ISingleAction&, FCombatCharacter&, const FBaseRestorerModel&, int32);

    /**
     * 应用状态性动作结果。
     * 参数含义同@code FCombatSystem::DoStatusAction \endcode
     */
    static void ApplyStatusResult(const ISingleAction&, FCombatCharacter&, const FBaseStatusModel&, int32);

public:
    /**
     * 执行攻击性动作。攻击类型0~3已经有默认行为，传入其它值将回调@code ISingleAction::CustomApplyAttackResult \endcode
     * 方法。提供一个回调函数，在计算出伤害值之后、对目标角色执行伤害结算之前调用，用于更新UI
     * @param action 攻击动作
     * @param character 被攻击者
     * @param type 攻击类型
     * @param cb 用于更新UI的回调函数
     */
    void DoAttackAction(const ISingleAction& action, ICharacterCombatDelegate& character, int32 type, FAttackCallback cb) const;

    /**
     * 执行恢复性动作。类型0已有默认行为，传入其他值将回调@code ISingleAction::CustomApplyRestorerResult \endcode
     * 方法。提供一个回调函数，在计算出伤害值之后、对目标角色执行伤害结算之前调用，用于更新UI
     * @param action 恢复动作
     * @param character 恢复目标
     * @param type 恢复类型
     * @param cb 用于更新UI的回调函数
     */
    void DoRestorerAction(const ISingleAction& action, ICharacterCombatDelegate& character, int32 type, FRestorerCallback cb) const;

    /**
     * 执行状态性动作。类型0已经有默认行为，传入其它值将回调@code ISingleAction::CustomApplyStatusResult \endcode
     * 方法。提供一个回调函数，在计算出伤害值之后、对目标角色执行伤害结算之前调用，用于更新UI
     * @param action 状态动作
     * @param character 应用目标
     * @param type 类型
     * @param cb 用于更新UI的回调函数
     */
    void DoStatusAction(const ISingleAction& action, ICharacterCombatDelegate& character, int32 type, FStatusCallback cb) const;

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
    bool IsCharacterExist(const ICharacterCombatDelegate&) const;

    bool BattleIsOver() const;
    /**
     * 获取战斗结束后玩家一方是否胜利。
     * @warning 此方法仅在战斗结束(@see BattleIsOver)后才具有正确的返回值，如果战斗未结束，返回值是未知的。
     */
    bool IsPlayerWinned() const;

private:
    mutable FBattleBeginEvent BattleBeginEvent;
    mutable FBattleFinishedEvent BattleFinishedEvent;
    mutable FCharacterWillActEvent CharacterWillActEvent;
    mutable FCharacterFinishActEvent CharacterFinishActEvent;

    TArray<TSharedRef<FCombatCharacter>> Characters;
    TSharedRef<ICharacterRoundDispatcher> Dispatcher;
    // 存储每个参战人物的回合管理器实例。不直接存对象而是存储智能指针，原因是这个列表可能会有增加操作，
    // 那么就有可能会导致列表存储内存重分配，造成指向其中元素实例的指针悬挂（在FCharacterRoundManager里
    // 面会用到自身的this指针的值。）
    // TArray<TSharedRef<FRoundManager>> RoundManagers;

    // 最后一次出手的人
    FCombatCharacter *CharacterActLast;
};
