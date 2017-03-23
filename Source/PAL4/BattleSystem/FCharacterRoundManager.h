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
    // δ�ж�״̬�������ﴦ���ж������յ�λ��
    NoAction,
    // ׼���ж�
    BeforeAction,
    // �����ж�
    OnAction,
    // �ж���ϣ���������δ�ж�״̬
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

    // �»غϿ�ʼ�¼�
    FRoundBeginEvent& OnNewRoundBegin() { return RoundBeginEvent; }
    // ��ǰ�غϽ����¼�
    FRoundFinishedEvent& OnRoundFinished() { return RoundFinishedEvent; }

    uint32 GetCurrentRoundNum() const { return RoundNum; }

    ECharacterRoundStatus GetCurrentRoundStatus() const { return RoundStatus; }

    TSharedRef<ISupportRoundAction>& GetBindAction() { return RoundAction; }

    const TSharedRef<ISupportRoundAction>& GetBindAction() const { return RoundAction; }

    /*
     * ����ӳٻغϵ����¼�����ָ���Ļغ���֮����á�
     * @param delayNum �ӳٻغ���
     * @param callWhenBegin �Ƿ�Ӧ���ڻغϿ�ʼʱ���ã�trueΪ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
     * @param func ���÷���
     * @return һ��keyֵ������ȡ���¼�
     */
    uint32 AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, std::function<void()> func);

    /*
     * ����ӳٻغϵ����¼�����ָ���Ļغϵ��á�
     * @param roundNum ָ���غ���
     * @param callWhenBegin �Ƿ�Ӧ���ڻغϿ�ʼʱ���ã�trueΪ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
     * @param callIfPast ���ǰ��������ָ���ĵ���ʱ���Ѿ����ˣ����紫��غ���С�ڵ�ǰ�غϣ����Ƿ�Ӧ����������
     * @param func ���÷���
     * @return һ��keyֵ������ȡ���¼�������0����ʾ����ʱ���ѹ�
     */
    uint32 AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, std::function<void()> func);

    /*
     * �Ƴ��ӳٵ��õ��¼���ǰ�����¼���δ�����ȹ�
     * @param key ������¼�ʱ���ص�keyֵ
     */
    void RemoveDelayCallFunc(uint32 key);

private:
    void DoRoundAction();

private:
    // �¼�
    FRoundBeginEvent RoundBeginEvent;
    FRoundFinishedEvent RoundFinishedEvent;

    TSharedRef<ISupportRoundAction> RoundAction;
    FRoundFunc RoundFunc;
    uint32 RoundNum;
    ECharacterRoundStatus RoundStatus;

    // ��������ӳٵ���ʱ���ص�keyֵ��ÿ����Ӷ�����������ʹ��ԭ������
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
