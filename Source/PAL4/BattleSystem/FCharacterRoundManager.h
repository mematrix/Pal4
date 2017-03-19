// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include <queue>
#include <vector>

class FBattleSystem;
class ISupportRoundAction;

/**
 *
 */
class PAL4_API FCharacterRoundManager
{
    friend class FBattleSystem;

private:
    struct PAL4_API FDelayCallFuncWrapper
    {
        uint32 RoundTimeWhenCall;
        std::function<void()> DelayCalledFunc;

        explicit FDelayCallFuncWrapper(uint32 time = 0, std::function<void()> func = nullptr) :
            RoundTimeWhenCall(time),
            DelayCalledFunc(std::move(func)) { }

        FDelayCallFuncWrapper(const FDelayCallFuncWrapper&) = default;

        FDelayCallFuncWrapper(FDelayCallFuncWrapper&& other) :
            RoundTimeWhenCall(other.RoundTimeWhenCall),
            DelayCalledFunc(std::move(other.DelayCalledFunc))
        {
            other.RoundTimeWhenCall = 0;
            other.DelayCalledFunc = nullptr;
        }

        FDelayCallFuncWrapper& operator=(const FDelayCallFuncWrapper& other) { Swap(FDelayCallFuncWrapper(other)); }
        FDelayCallFuncWrapper& operator=(FDelayCallFuncWrapper&& other) { Swap(other); }

        void Swap(FDelayCallFuncWrapper& other) noexcept
        {
            std::swap(RoundTimeWhenCall, other.RoundTimeWhenCall);
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

    typedef std::priority_queue<FDelayCallFuncWrapper, std::vector<FDelayCallFuncWrapper>, FRoundTimeComparator> FRoundFunc;

public:
    DECLARE_EVENT_TwoParams(FCharacterRoundManager, FRoundBeginEvent, const FCharacterRoundManager&, uint32)
    DECLARE_EVENT_OneParam(FCharacterRoundManager, FRoundFinishedEvent, const FCharacterRoundManager&)

public:
    explicit FCharacterRoundManager(ISupportRoundAction& action) : RoundAction(action) { }
    FCharacterRoundManager(const FCharacterRoundManager&) = delete;
    ~FCharacterRoundManager() = default;

    FCharacterRoundManager& operator=(const FCharacterRoundManager&) = delete;

    FRoundBeginEvent& OnNewRoundBegin() { return RoundBeginEvent; }
    FRoundFinishedEvent& OnRoundFinished() { return RoundFinishedEvent; }

private:
    FRoundBeginEvent RoundBeginEvent;
    FRoundFinishedEvent RoundFinishedEvent;

private:
    ISupportRoundAction& RoundAction;
    FRoundFunc RoundFunc;
};
