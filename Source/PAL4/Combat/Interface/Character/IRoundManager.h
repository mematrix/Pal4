#pragma once

#include <functional>

#include <Delegate.h>


enum class PAL4_API ECharacterRoundStatus
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

class PAL4_API IRoundManager
{
public:
    DECLARE_EVENT_TwoParams(IRoundManager, FRoundBeginEvent, const IRoundManager&, uint32)
    DECLARE_EVENT_TwoParams(IRoundManager, FRoundFinishedEvent, const IRoundManager&, uint32)

public:
    IRoundManager() : 
        RoundBeginEvent(),
        RoundFinishedEvent(),
        RoundNum(0),
        RoundStatus(ECharacterRoundStatus::NoAction)
    {
    }
    IRoundManager(const IRoundManager&) = default;
    IRoundManager(IRoundManager&&) = default;

    virtual ~IRoundManager() = default;

    IRoundManager& operator=(const IRoundManager&) = default;
    IRoundManager& operator=(IRoundManager&&) = default;

    // �»غϿ�ʼ�¼�
    FRoundBeginEvent& OnNewRoundBegin() const { return RoundBeginEvent; }
    // ��ǰ�غϽ����¼�
    FRoundFinishedEvent& OnRoundFinished() const { return RoundFinishedEvent; }

    uint32 GetCurrentRoundNum() const { return RoundNum; }

    ECharacterRoundStatus GetCurrentRoundStatus() const { return RoundStatus; }

    /*
    * ����ӳٻغϵ����¼�����ָ���Ļغ���֮����á�
    * @param delayNum �ӳٻغ���
    * @param callWhenBegin �Ƿ�Ӧ���ڻغϿ�ʼʱ���ã�trueΪ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
    * @param func ���÷���
    * @return һ��keyֵ������ȡ���¼�
    */
    virtual uint32 AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, const std::function<void()>& func) = 0;

    /*
    * ����ӳٻغϵ����¼�����ָ���Ļغϵ��á�
    * @param roundNum ָ���غ���
    * @param callWhenBegin �Ƿ�Ӧ���ڻغϿ�ʼʱ���ã�trueΪ�ڻغϿ�ʼ���ã�falseΪ����ʱ����
    * @param callIfPast ���ǰ��������ָ���ĵ���ʱ���Ѿ����ˣ����紫��غ���С�ڵ�ǰ�غϣ����Ƿ�Ӧ����������
    * @param func ���÷���
    * @return һ��keyֵ������ȡ���¼�������0����ʾ����ʱ���ѹ�
    */
    virtual uint32 AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, const std::function<void()>& func) = 0;

    /*
    * �Ƴ��ӳٵ��õ��¼���ǰ�����¼���δ�����ȹ�
    * @param key ������¼�ʱ���ص�keyֵ
    */
    virtual void RemoveDelayCallFunc(uint32 key) = 0;

protected:
    // �غϿ�ʼ�¼�
    mutable FRoundBeginEvent RoundBeginEvent;
    // �غϽ����¼�
    mutable FRoundFinishedEvent RoundFinishedEvent;

    // ��ǰ�غ���
    uint32 RoundNum;
    // �����ж�״̬��δ�ж��������ж��������ж����ж����
    ECharacterRoundStatus RoundStatus;
};
