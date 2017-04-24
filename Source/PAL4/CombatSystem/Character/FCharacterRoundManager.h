// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include <deque>

#include "Core/PriorityQueue.h"
#include "BattleDelegate/Character/ICharacterRoundManager.h"

class IRoundActionHandler;


/**
 *
 */
class PAL4_API FCharacterRoundManager : public ICharacterRoundManager
{
private:
    struct PAL4_API FDelayCallFuncWrapper
    {
        uint32 Key;
        uint32 RoundNumWhenCall;
        bool CallWhenRoundBegin;
        std::function<void()> DelayCalledFunc;

        explicit FDelayCallFuncWrapper(uint32 key, uint32 num = 0, bool callWhenBegin = true, std::function<void()> func = nullptr) :
            Key(key),
            RoundNumWhenCall(num),
            CallWhenRoundBegin(callWhenBegin),
            DelayCalledFunc(std::move(func))
        {
        }

        FDelayCallFuncWrapper(const FDelayCallFuncWrapper&) = default;
        FDelayCallFuncWrapper(FDelayCallFuncWrapper&& other) = default;

        FDelayCallFuncWrapper& operator=(const FDelayCallFuncWrapper& other) = default;
        FDelayCallFuncWrapper& operator=(FDelayCallFuncWrapper&& other) = default;

        bool operator==(const FDelayCallFuncWrapper& other) const
        {
            return Key == other.Key /*&& RoundNumWhenCall == other.RoundNumWhenCall && CallWhenRoundBegin == other.CallWhenRoundBegin*/;
        }

        void Swap(FDelayCallFuncWrapper& other) noexcept
        {
            using std::swap;
            swap(Key, other.Key);
            swap(RoundNumWhenCall, other.RoundNumWhenCall);
            swap(CallWhenRoundBegin, other.CallWhenRoundBegin);
            DelayCalledFunc.swap(other.DelayCalledFunc);
        }
    };

    friend void swap(FDelayCallFuncWrapper& left, FDelayCallFuncWrapper& right) noexcept(noexcept(left.Swap(right)));

    class PAL4_API FRoundTimeComparator
    {
    public:
        bool operator()(const FDelayCallFuncWrapper& left, const FDelayCallFuncWrapper& right) const
        {
            return (left.RoundNumWhenCall > right.RoundNumWhenCall ||
                (left.RoundNumWhenCall == right.RoundNumWhenCall && left.CallWhenRoundBegin));
        }
    };

    typedef PriorityQueue<FDelayCallFuncWrapper, std::deque<FDelayCallFuncWrapper>, FRoundTimeComparator> FRoundFunc;


public:
    explicit FCharacterRoundManager(IRoundActionHandler&);
    FCharacterRoundManager(const FCharacterRoundManager&) = default;
    FCharacterRoundManager(FCharacterRoundManager&&) = default;

    FCharacterRoundManager& operator=(const FCharacterRoundManager&) = delete;
    FCharacterRoundManager& operator=(FCharacterRoundManager&&) = delete;

    // void Swap(FCharacterRoundManager& other);

    IRoundActionHandler& GetBindAction() { return RoundAction; }
    const IRoundActionHandler& GetBindAction() const { return RoundAction; }

    /**
     * 添加延迟回合调用事件，在指定的回合数之后调用。
     * @param delayNum 延迟回合数
     * @param callWhenBegin 是否应该在回合开始时调用，true为在回合开始调用，false为结束时调用
     * @param func 调用方法
     * @return 一个key值，用于取消事件
     */
    uint32 AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, const std::function<void()>& func) override;

    /**
     * 添加延迟回合调用事件，在指定的回合调用。
     * @param roundNum 指定回合数
     * @param callWhenBegin 是否应该在回合开始时调用，true为在回合开始调用，false为结束时调用
     * @param callIfPast 如果前两个参数指定的调用时机已经过了（比如传入回合数小于当前回合），是否应该立即调用
     * @param func 调用方法
     * @return 一个key值，用于取消事件。或者0，表示调用时机已过
     */
    uint32 AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, const std::function<void()>& func) override;

    /**
     * 移除延迟调用的事件。前提是事件还未被调度过
     * @param key 在添加事件时返回的key值
     */
    void RemoveDelayCallFunc(uint32 key) override;

    /**
     * 执行回合动作。
     * @param shouldSkipAction 指示是否应该跳过当前角色的行动，例如角色处于定、眠状态，
     * 将会跳过@code IRoundActionHandler::DoAction()\endcode 的执行，但是不会跳过其它方法
     */
    void DoRoundAction(bool shouldSkipAction = false);

private:
    // 支持回合处理的类型引用。通常为战场中的人物或AI
    IRoundActionHandler& RoundAction;
    // 保存延迟回调的方法
    FRoundFunc RoundFunc;

    // 用于添加延迟调用时返回的key值，每次添加都递增。考虑使用原子类型
    uint32 DelayFuncKey;
};

//template<>
//void std::swap<FCharacterRoundManager>(FCharacterRoundManager& left, FCharacterRoundManager& right) noexcept(noexcept(left.Swap(right)));

