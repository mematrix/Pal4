// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include <deque>

#include <Core/PriorityQueue.h>

class FBattleSystem;
class ISupportRoundAction;

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
        std::function<void()> DelayCalledFunc;

        explicit FDelayCallFuncWrapper(uint32 key, uint32 time = 0, std::function<void()> func = nullptr) :
            Key(key),
            RoundTimeWhenCall(time),
            DelayCalledFunc(std::move(func)) { }

        FDelayCallFuncWrapper(const FDelayCallFuncWrapper&) = default;

        FDelayCallFuncWrapper(FDelayCallFuncWrapper&& other) :
            Key(other.Key),
            RoundTimeWhenCall(other.RoundTimeWhenCall),
            DelayCalledFunc(std::move(other.DelayCalledFunc))
        {
            other.Key = 0;
            other.RoundTimeWhenCall = 0;
            other.DelayCalledFunc = nullptr;
        }

        FDelayCallFuncWrapper& operator=(const FDelayCallFuncWrapper& other) { Swap(FDelayCallFuncWrapper(other)); }
        FDelayCallFuncWrapper& operator=(FDelayCallFuncWrapper&& other) { Swap(other); }

        bool operator==(const FDelayCallFuncWrapper& other) { return Key == other.Key && RoundTimeWhenCall == other.RoundTimeWhenCall; }

        void Swap(FDelayCallFuncWrapper& other) noexcept
        {
            using std::swap;
            swap(Key, other.Key);
            swap(RoundTimeWhenCall, other.RoundTimeWhenCall);
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


void swap(FCharacterRoundManager::FDelayCallFuncWrapper& left, FCharacterRoundManager::FDelayCallFuncWrapper& right)
{
    left.Swap(right);
}

//namespace std
//{
//    template<> void swap<FCharacterRoundManager::FDelayCallFuncWrapper>(FCharacterRoundManager::FDelayCallFuncWrapper& left,
//        FCharacterRoundManager::FDelayCallFuncWrapper& right)
//    {
//        left.Swap(right);
//    }
//}
