#pragma once

#include <Delegate.h>


enum class PAL4_API ERoundStatus
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
 * 人物回合管理。提供回合开始结束事件
 */
class PAL4_API IRoundManager
{
public:
    DECLARE_EVENT_TwoParams(IRoundManager, FRoundBeginEvent, const IRoundManager&, uint32)
    DECLARE_EVENT_TwoParams(IRoundManager, FRoundFinishedEvent, const IRoundManager&, uint32)

protected:
    // 回合开始事件
    mutable FRoundBeginEvent RoundBeginEvent;
    // 回合结束事件
    mutable FRoundFinishedEvent RoundFinishedEvent;

    // 当前回合数
    uint32 RoundNum;
    // 人物行动状态：未行动，即将行动，正在行动，行动完毕
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

    // 新回合开始事件
    FRoundBeginEvent& OnNewRoundBegin() const { return RoundBeginEvent; }

    // 当前回合结束事件
    FRoundFinishedEvent& OnRoundFinished() const { return RoundFinishedEvent; }

    // 获取关联人物当前回合
    uint32 GetCurrentRoundNum() const { return RoundNum; }

    // 获取关联人物当前回合内状态
    ERoundStatus GetCurrentRoundStatus() const { return RoundStatus; }

};
