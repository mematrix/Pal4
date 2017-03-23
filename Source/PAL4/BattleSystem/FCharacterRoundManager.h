// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include <deque>

#include <SharedPointer.h>

#include "Core/PriorityQueue.h"

class FBattleSystem;
class ISupportRoundAction;

enum class ECharacterRoundStatus
{
    // 未行动状态，即人物处于行动条非终点位置
    NoAction,
    // 准备行动
    BeforeAction,
    // 正在行动
    OnAction,
    // 行动完毕，即将进入未行动状态
    PostAction
};

/**
 *
 */
class PAL4_API FCharacterRoundManager
{
    class FDelayCallFuncWrapper;

    friend void swap(FDelayCallFuncWrapper&, FDelayCallFuncWrapper&);
    //friend void std::swap<FDelayCallFuncWrapper>(FDelayCallFuncWrapper&, FDelayCallFuncWrapper&);
    friend class FBattleSystem;

private:
    struct PAL4_API FDelayCallFuncWrapper
    {
        //friend void std::swap<FDelayCallFuncWrapper>(FDelayCallFuncWrapper&, FDelayCallFuncWrapper&);

        uint32 Key;
        uint32 RoundTimeWhenCall;
        bool CallWhenRoundBegin;
        std::function<void()> DelayCalledFunc;

        explicit FDelayCallFuncWrapper(uint32 key, uint32 time = 0, bool callWhenBegin = true, std::function<void()> func = nullptr) :
            Key(key),
            RoundTimeWhenCall(time),
            CallWhenRoundBegin(callWhenBegin),
            DelayCalledFunc(std::move(func)) { }

        FDelayCallFuncWrapper(const FDelayCallFuncWrapper&) = default;

        FDelayCallFuncWrapper(FDelayCallFuncWrapper&& other) :
            Key(other.Key),
            RoundTimeWhenCall(other.RoundTimeWhenCall),
            CallWhenRoundBegin(other.CallWhenRoundBegin),
            DelayCalledFunc(std::move(other.DelayCalledFunc))
        {
            other.Key = -1;
            other.RoundTimeWhenCall = 0;
            other.DelayCalledFunc = nullptr;
        }

        FDelayCallFuncWrapper& operator=(const FDelayCallFuncWrapper& other) { Swap(FDelayCallFuncWrapper(other)); }
        FDelayCallFuncWrapper& operator=(FDelayCallFuncWrapper&& other) { Swap(other); }

        bool operator==(const FDelayCallFuncWrapper& other)
        {
            return Key == other.Key /*&& RoundTimeWhenCall == other.RoundTimeWhenCall && CallWhenRoundBegin == other.CallWhenRoundBegin*/;
        }

        void Swap(FDelayCallFuncWrapper& other) noexcept
        {
            using std::swap;
            swap(Key, other.Key);
            swap(RoundTimeWhenCall, other.RoundTimeWhenCall);
            swap(CallWhenRoundBegin, other.CallWhenRoundBegin);
            DelayCalledFunc.swap(other.DelayCalledFunc);
        }
    };

    class PAL4_API FRoundTimeComparator
    {
    public:
        bool operator()(const FDelayCallFuncWrapper& left, const FDelayCallFuncWrapper& right)
        {
            return left.RoundTimeWhenCall > right.RoundTimeWhenCall;
        }
    };

    typedef PriorityQueue<FDelayCallFuncWrapper, std::deque<FDelayCallFuncWrapper>, FRoundTimeComparator> FRoundFunc;

public:
    DECLARE_EVENT_TwoParams(FCharacterRoundManager, FRoundBeginEvent, const FCharacterRoundManager&, uint32)
    DECLARE_EVENT_OneParam(FCharacterRoundManager, FRoundFinishedEvent, const FCharacterRoundManager&)

public:
    explicit FCharacterRoundManager(TSharedRef<ISupportRoundAction> action);
    FCharacterRoundManager(const FCharacterRoundManager&) = delete;
    FCharacterRoundManager(FCharacterRoundManager&&);
    ~FCharacterRoundManager() = default;

    FCharacterRoundManager& operator=(const FCharacterRoundManager&) = delete;
    FCharacterRoundManager& operator=(FCharacterRoundManager&&);

    void Swap(FCharacterRoundManager& other);

    // 新回合开始事件
    FRoundBeginEvent& OnNewRoundBegin() { return RoundBeginEvent; }
    // 当前回合结束事件
    FRoundFinishedEvent& OnRoundFinished() { return RoundFinishedEvent; }

    uint32 GetCurrentRoundNum() const { return RoundNum; }

    ECharacterRoundStatus GetCurrentRoundStatus() const { return RoundStatus; }

    TSharedRef<ISupportRoundAction>& GetBindAction() { return RoundAction; }

    const TSharedRef<ISupportRoundAction>& GetBindAction() const { return RoundAction; }

    /*
     * 添加延迟回合调用事件，在指定的回合数之后调用。
     * @param delayNum 延迟回合数
     * @param callWhenBegin 是否应该在回合开始时调用，true为在回合开始调用，false为结束时调用
     * @param func 调用方法
     * @return 一个key值，用于取消事件
     */
    uint32 AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, std::function<void()> func);

    /*
     * 添加延迟回合调用事件，在指定的回合调用。
     * @param roundNum 指定回合数
     * @param callWhenBegin 是否应该在回合开始时调用，true为在回合开始调用，false为结束时调用
     * @param callIfPast 如果前两个参数指定的调用时机已经过了（比如传入回合数小于当前回合），是否应该立即调用
     * @param func 调用方法
     * @return 一个key值，用于取消事件。或者0，表示调用时机已过
     */
    uint32 AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, std::function<void()> func);

    /*
     * 移除延迟调用的事件。前提是事件还未被调度过
     * @param key 在添加事件时返回的key值
     */
    void RemoveDelayCallFunc(uint32 key);

private:
    void DoRoundAction();

private:
    // 事件
    FRoundBeginEvent RoundBeginEvent;
    FRoundFinishedEvent RoundFinishedEvent;

    TSharedRef<ISupportRoundAction> RoundAction;
    FRoundFunc RoundFunc;
    uint32 RoundNum;
    ECharacterRoundStatus RoundStatus;

    // 用于添加延迟调用时返回的key值，每次添加都递增。考虑使用原子类型
    uint32 DelayFuncKey;
};


void swap(FCharacterRoundManager::FDelayCallFuncWrapper& left, FCharacterRoundManager::FDelayCallFuncWrapper& right)
{
    left.Swap(right);
}

namespace std
{
    template<> void swap<FCharacterRoundManager>(FCharacterRoundManager& left, FCharacterRoundManager& right)
    {
        left.Swap(right);
    }
}

//namespace std
//{
//    template<> void swap<FCharacterRoundManager::FDelayCallFuncWrapper>(FCharacterRoundManager::FDelayCallFuncWrapper& left,
//        FCharacterRoundManager::FDelayCallFuncWrapper& right)
//    {
//        left.Swap(right);
//    }
//}
