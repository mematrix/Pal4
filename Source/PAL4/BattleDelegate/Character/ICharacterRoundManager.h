#pragma once

#include <functional>

#include <Delegate.h>


enum class PAL4_API ECharacterRoundStatus
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

class PAL4_API ICharacterRoundManager
{
public:
    DECLARE_EVENT_TwoParams(ICharacterRoundManager, FRoundBeginEvent, const ICharacterRoundManager&, uint32)
    DECLARE_EVENT_OneParam(ICharacterRoundManager, FRoundFinishedEvent, const ICharacterRoundManager&)

public:
    ICharacterRoundManager() : 
        RoundBeginEvent(),
        RoundFinishedEvent(),
        RoundNum(0),
        RoundStatus(ECharacterRoundStatus::NoAction)
    {
    }
    ICharacterRoundManager(const ICharacterRoundManager&) = default;
    ICharacterRoundManager(ICharacterRoundManager&&) = default;

    virtual ~ICharacterRoundManager()
    {
    }

    ICharacterRoundManager& operator=(const ICharacterRoundManager&) = default;
    ICharacterRoundManager& operator=(ICharacterRoundManager&&) = default;

    // 新回合开始事件
    FRoundBeginEvent& OnNewRoundBegin() { return RoundBeginEvent; }
    // 当前回合结束事件
    FRoundFinishedEvent& OnRoundFinished() { return RoundFinishedEvent; }

    uint32 GetCurrentRoundNum() const { return RoundNum; }

    ECharacterRoundStatus GetCurrentRoundStatus() const { return RoundStatus; }

    /*
    * 添加延迟回合调用事件，在指定的回合数之后调用。
    * @param delayNum 延迟回合数
    * @param callWhenBegin 是否应该在回合开始时调用，true为在回合开始调用，false为结束时调用
    * @param func 调用方法
    * @return 一个key值，用于取消事件
    */
    virtual uint32 AddDelayCallFunc(uint32 delayNum, bool callWhenBegin, const std::function<void()>& func) = 0;

    /*
    * 添加延迟回合调用事件，在指定的回合调用。
    * @param roundNum 指定回合数
    * @param callWhenBegin 是否应该在回合开始时调用，true为在回合开始调用，false为结束时调用
    * @param callIfPast 如果前两个参数指定的调用时机已经过了（比如传入回合数小于当前回合），是否应该立即调用
    * @param func 调用方法
    * @return 一个key值，用于取消事件。或者0，表示调用时机已过
    */
    virtual uint32 AddDelayCallFuncByRound(uint32 roundNum, bool callWhenBegin, bool callIfPast, const std::function<void()>& func) = 0;

    /*
    * 移除延迟调用的事件。前提是事件还未被调度过
    * @param key 在添加事件时返回的key值
    */
    virtual void RemoveDelayCallFunc(uint32 key) = 0;

protected:
    // 回合开始事件
    FRoundBeginEvent RoundBeginEvent;
    // 回合结束事件
    FRoundFinishedEvent RoundFinishedEvent;

    // 当前回合数
    uint32 RoundNum;
    // 人物行动状态：未行动，即将行动，正在行动，行动完毕
    ECharacterRoundStatus RoundStatus;
};
