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

    void SetStatusResultCallback(const FStatusFunc&);

    /**
     * 应用状态性动作结果。类型0已经有默认行为，传入其它值将调用自定义处理方法。要设置自定义处理函数，
     * 参见@code SetStatusResultCallback(const std::function<...>&) \endcode 。
     * @param model 状态动作模型类。@code model.type \endcode 为0对应了默认行为，将会调用默认的方式处理状态逻辑
     */
    void ApplyStatusResult(const ActionResultModel<FBaseStatusModel>& model);

    void SetAttackResultCallback(const FAttackFunc&);

    /**
     * 应用攻击性动作结果。攻击类型0~3已经有默认行为，传入其它值将调用自定义处理方法。要设置自定义处理函数，
     * 参见@code SetAttackResultCallback(const std::function<...>&) \endcode 。
     * @param model 攻击动作模型类。@code model.type \endcode 为0,1,2,3对应普通攻击、仙术攻击、技能攻击、物品攻击
     */
    void ApplyAttackResult(const ActionResultModel<FBaseAttackModel>& model);

    void SetRestorerResultCallback(const FRestorerFunc&);

    /**
     * 应用恢复性动作结果。类型0已有默认行为，传入其他值将调用自定义处理方法。要设置自定义处理函数，
     * 参见@code SetRestorerResultCallback(const std::function<...>&) \endcode 。
     * @param model 恢复动作模型类。@code model.type \endcode 为0对应了默认行为，将会调用默认的方式处理恢复逻辑
     */
    void ApplyRestorerResult(const ActionResultModel<FBaseRestorerModel>& model);

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
    TSharedRef<FBattleCharacter>* FindCharacter(const ICharacterBattleDelegate*);

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

    FStatusFunc CustomStatusFunc;
    FAttackFunc CustomAttackFunc;
    FRestorerFunc CustomRestorerFunc;

    // 最后一次出手的人
    FBattleCharacter *CharacterActLast;
};
