// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <utility>
#include <Platform.h>

class FCharacterRoundManager;

/**
 * 处理回合动作的回调接口。每次只能绑定单个@see FCharacterRoundManager，绑定单个玩家角色或AI角色
 */
class PAL4_API IRoundActionHandler
{
    friend class FCharacterRoundManager;

public:
    IRoundActionHandler() noexcept : RoundManager(nullptr) { }
    IRoundActionHandler(const IRoundActionHandler&) = delete;
    IRoundActionHandler(IRoundActionHandler&&) noexcept;

    IRoundActionHandler& operator=(IRoundActionHandler&) = delete;
    IRoundActionHandler& operator=(IRoundActionHandler&&) noexcept;

	virtual ~IRoundActionHandler() { }

    FCharacterRoundManager* GetRoundManager() const { return RoundManager; }

    // virtual void WaitingAct() { }

    virtual void OnNewRoundBegin(uint32 roundNum) { }

    virtual void OnAction() = 0;

    virtual void OnRoundFinished() { }

private:
    void SwapManager(IRoundActionHandler& other) noexcept
    {
        std::swap(RoundManager, other.RoundManager);
    }

    FCharacterRoundManager *RoundManager;
};
