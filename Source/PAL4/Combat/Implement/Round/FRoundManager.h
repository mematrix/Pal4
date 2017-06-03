// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include <deque>
#include <list>

#include "Core/PriorityQueue.h"
#include "Combat/Interface/Round/IRoundManager.h"

class ICharacterDelegate;


/**
 * �غϹ����ࡣ֧������غ϶������ȣ�֧�ֻغ���ػص�����Ĺ�����ӡ�ɾ�����Լ����ֵ���������ʽ��
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
     * ����ӳٻغϵ��÷�������ָ���Ļغ���֮����á�
     * @param delayNum �ӳٻغ���
     * @param callWhenBegin �Ƿ�Ӧ���ڻغϿ�ʼʱ���ã�trueΪ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
     * @param func ���÷���
     * @return һ��keyֵ������ȡ��ָ���ص�
     */
    uint32 AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, const std::function<void()>& func);

    /**
     * ����ӳٻغϵ��÷�������ָ���Ļغϵ��á�
     * @param roundNum ָ���غ���
     * @param callWhenBegin �Ƿ�Ӧ���ڻغϿ�ʼʱ���ã�trueΪ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
     * @param callIfPast ���ǰ��������ָ���ĵ���ʱ���Ѿ����ˣ����紫��غ���С�ڵ�ǰ�غϣ����Ƿ�Ӧ����������
     * @param func ���÷���
     * @return һ��keyֵ������ȡ��ָ���ص�������0����ʾ����ʱ���ѹ�
     */
    uint32 AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, const std::function<void()>& func);

    /**
     * �Ƴ��ӳٵ��õķ�����ǰ���Ƿ�����δ�����ȹ�
     * @param key ����ӻص�ʱ���ص�keyֵ
     */
    void RemoveDelayCallFunc(uint32 key);

    /**
     * @brief ���ÿ�غϴ����ķ���
     * @param callWhenBegin �Ƿ��ڻغϿ�ʼʱ���á�true��ʾ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
     * @param func �ص�����
     * @return һ��keyֵ������ȡ��ָ���ص���
     */
    uint32 AddRoundFunc(bool callWhenBegin, const std::function<void()>& func);

    /**
     * @brief �Ƴ�ָ���Ļغϻص�����
     * @param key ����ӻص�ʱ���ص�keyֵ
     */
    void RemoveRoundFunc(uint32 key);

    /**
     * ִ�лغ϶�����
     * @param shouldSkipAction ָʾ�Ƿ�Ӧ��������ǰ��ɫ���ж��������ɫ���ڶ�����״̬��
     * ��������@code IRoundActionHandler::DoAction()\endcode ��ִ�У����ǲ���������������
     */
    void DoRoundAction(bool shouldSkipAction = false);

private:
    // ս���е������AI
    ICharacterDelegate& Character;
    // �����ӳٻص��ķ���
    FRoundFuncQueue DelayRoundFuncs;
    // ����ÿ�غϴ����Ļص������б�
    FRoundFuncList RoundFuncs;

    // ��������ӳٵ���ʱ���ص�keyֵ��ÿ����Ӷ�����������ʹ��ԭ������
    uint32 FuncKey;
};

//template<>
//void std::swap<FRoundManager>(FRoundManager& left, FRoundManager& right) noexcept(noexcept(left.Swap(right)));

