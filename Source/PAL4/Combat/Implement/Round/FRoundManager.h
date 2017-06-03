// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include <deque>
#include <list>

#include "Core/PriorityQueue.h"
#include "Combat/Interface/Round/IRoundManager.h"

class ICharacterDelegate;


/**
 * 回合管理类。支持人物回合动作调度，支持回合相关回调对象的管理（添加、删除，以及多种调度周期形式）
 */
class PAL4_API FRoundManager : public IRoundManager
{
    struct PAL4_API FRoundFuncWrapper
    {
        uint32 Key;
        uint32 RoundNumWhenCall;
        bool CallWhenRoundBegin;
        std::function<void()> Func;

        explicit FRoundFuncWrapper(uint32 key, uint32 num = 0, bool callWhenBegin = true, std::function<void()> func = nullptr) :
            Key(key),
            RoundNumWhenCall(num),
            CallWhenRoundBegin(callWhenBegin),
            Func(std::move(func))
        {
        }

        FRoundFuncWrapper(const FRoundFuncWrapper&) = default;
        FRoundFuncWrapper(FRoundFuncWrapper&& other) = default;

        FRoundFuncWrapper& operator=(const FRoundFuncWrapper& other) = default;
        FRoundFuncWrapper& operator=(FRoundFuncWrapper&& other) = default;

        bool operator==(const FRoundFuncWrapper& other) const
        {
            return Key == other.Key /*&& RoundNumWhenCall == other.RoundNumWhenCall && CallWhenRoundBegin == other.CallWhenRoundBegin*/;
        }

        void Swap(FRoundFuncWrapper& other) noexcept
        {
            using std::swap;
            swap(Key, other.Key);
            swap(RoundNumWhenCall, other.RoundNumWhenCall);
            swap(CallWhenRoundBegin, other.CallWhenRoundBegin);
            Func.swap(other.Func);
        }
    };

    // friend void swap(FRoundFuncWrapper& left, FRoundFuncWrapper& right) noexcept(noexcept(left.Swap(right)));

    struct PAL4_API FRoundTimeComparator
    {
        bool operator()(const FRoundFuncWrapper& left, const FRoundFuncWrapper& right) const
        {
            return (left.RoundNumWhenCall > right.RoundNumWhenCall ||
                (left.RoundNumWhenCall == right.RoundNumWhenCall && left.CallWhenRoundBegin));
        }
    };

    typedef PriorityQueue<FRoundFuncWrapper, std::deque<FRoundFuncWrapper>, FRoundTimeComparator> FRoundFuncQueue;
    typedef std::list<FRoundFuncWrapper> FRoundFuncList;


public:
    explicit FRoundManager(ICharacterDelegate&);
    FRoundManager(const FRoundManager&) = default;
    FRoundManager(FRoundManager&&) = default;

    FRoundManager& operator=(const FRoundManager&) = delete;
    FRoundManager& operator=(FRoundManager&&) = delete;

    // void Swap(FRoundManager& other);

    /**
     * 添加延迟回合调用方法，在指定的回合数之后调用。
     * @param delayNum 延迟回合数
     * @param callWhenBegin 是否应该在回合开始时调用，true为在回合开始调用，false为结束时调用
     * @param func 调用方法
     * @return 一个key值，用于取消指定回调
     */
    uint32 AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, const std::function<void()>& func);

    /**
     * 添加延迟回合调用方法，在指定的回合调用。
     * @param roundNum 指定回合数
     * @param callWhenBegin 是否应该在回合开始时调用，true为在回合开始调用，false为结束时调用
     * @param callIfPast 如果前两个参数指定的调用时机已经过了（比如传入回合数小于当前回合），是否应该立即调用
     * @param func 调用方法
     * @return 一个key值，用于取消指定回调。或者0，表示调用时机已过
     */
    uint32 AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, const std::function<void()>& func);

    /**
     * 移除延迟调用的方法。前提是方法还未被调度过
     * @param key 在添加回调时返回的key值
     */
    void RemoveDelayCallFunc(uint32 key);

    /**
     * @brief 添加每回合触发的方法
     * @param callWhenBegin 是否在回合开始时调用。true表示在回合开始调用，false为结束时调用
     * @param func 回调方法
     * @return 一个key值，用于取消指定回调。
     */
    uint32 AddRoundFunc(bool callWhenBegin, const std::function<void()>& func);

    /**
     * @brief 移除指定的回合回调方法
     * @param key 在添加回调时返回的key值
     */
    void RemoveRoundFunc(uint32 key);

    /**
     * 执行回合动作。
     * @param shouldSkipAction 指示是否应该跳过当前角色的行动，例如角色处于定、眠状态，
     * 将会跳过@code IRoundActionHandler::DoAction()\endcode 的执行，但是不会跳过其它方法
     */
    void DoRoundAction(bool shouldSkipAction = false);

private:
    // 战场中的人物或AI
    ICharacterDelegate& Character;
    // 保存延迟回调的方法
    FRoundFuncQueue DelayRoundFuncs;
    // 保存每回合触发的回调方法列表
    FRoundFuncList RoundFuncs;

    // 用于添加延迟调用时返回的key值，每次添加都递增。考虑使用原子类型
    uint32 FuncKey;
};

//template<>
//void std::swap<FRoundManager>(FRoundManager& left, FRoundManager& right) noexcept(noexcept(left.Swap(right)));

