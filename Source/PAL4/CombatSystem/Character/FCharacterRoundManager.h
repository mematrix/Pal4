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
     * ����ӳٻغϵ����¼�����ָ���Ļغ���֮����á�
     * @param delayNum �ӳٻغ���
     * @param callWhenBegin �Ƿ�Ӧ���ڻغϿ�ʼʱ���ã�trueΪ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
     * @param func ���÷���
     * @return һ��keyֵ������ȡ���¼�
     */
    uint32 AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, const std::function<void()>& func) override;

    /**
     * ����ӳٻغϵ����¼�����ָ���Ļغϵ��á�
     * @param roundNum ָ���غ���
     * @param callWhenBegin �Ƿ�Ӧ���ڻغϿ�ʼʱ���ã�trueΪ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
     * @param callIfPast ���ǰ��������ָ���ĵ���ʱ���Ѿ����ˣ����紫��غ���С�ڵ�ǰ�غϣ����Ƿ�Ӧ����������
     * @param func ���÷���
     * @return һ��keyֵ������ȡ���¼�������0����ʾ����ʱ���ѹ�
     */
    uint32 AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, const std::function<void()>& func) override;

    /**
     * �Ƴ��ӳٵ��õ��¼���ǰ�����¼���δ�����ȹ�
     * @param key ������¼�ʱ���ص�keyֵ
     */
    void RemoveDelayCallFunc(uint32 key) override;

    /**
     * ִ�лغ϶�����
     * @param shouldSkipAction ָʾ�Ƿ�Ӧ��������ǰ��ɫ���ж��������ɫ���ڶ�����״̬��
     * ��������@code IRoundActionHandler::DoAction()\endcode ��ִ�У����ǲ���������������
     */
    void DoRoundAction(bool shouldSkipAction = false);

private:
    // ֧�ֻغϴ�����������á�ͨ��Ϊս���е������AI
    IRoundActionHandler& RoundAction;
    // �����ӳٻص��ķ���
    FRoundFunc RoundFunc;

    // ��������ӳٵ���ʱ���ص�keyֵ��ÿ����Ӷ�����������ʹ��ԭ������
    uint32 DelayFuncKey;
};

//template<>
//void std::swap<FCharacterRoundManager>(FCharacterRoundManager& left, FCharacterRoundManager& right) noexcept(noexcept(left.Swap(right)));

