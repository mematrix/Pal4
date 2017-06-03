#pragma once

#include <Delegate.h>


enum class PAL4_API ERoundStatus
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
 * ����غϹ����ṩ�غϿ�ʼ�����¼�
 */
class PAL4_API IRoundManager
{
public:
    DECLARE_EVENT_TwoParams(IRoundManager, FRoundBeginEvent, const IRoundManager&, uint32)
    DECLARE_EVENT_TwoParams(IRoundManager, FRoundFinishedEvent, const IRoundManager&, uint32)

protected:
    // �غϿ�ʼ�¼�
    mutable FRoundBeginEvent RoundBeginEvent;
    // �غϽ����¼�
    mutable FRoundFinishedEvent RoundFinishedEvent;

    // ��ǰ�غ���
    uint32 RoundNum;
    // �����ж�״̬��δ�ж��������ж��������ж����ж����
    ERoundStatus RoundStatus;

public:
    IRoundManager() : 
        RoundBeginEvent(),
        RoundFinishedEvent(),
        RoundNum(0),
        RoundStatus(ERoundStatus::NoAction)
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

    // ��ȡ�������ﵱǰ�غ�
    uint32 GetCurrentRoundNum() const { return RoundNum; }

    // ��ȡ�������ﵱǰ�غ���״̬
    ERoundStatus GetCurrentRoundStatus() const { return RoundStatus; }

};
