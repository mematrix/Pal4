// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <SharedPointer.h>

#include "IRoundAction.h"


/**
 * 处理回合动作的回调接口。每次只能绑定单个@see FCharacterRoundManager，绑定单个玩家角色或AI角色
 */
class PAL4_API IRoundActionHandler
{
public:
    virtual ~IRoundActionHandler() = default;

    virtual void OnNewRoundBegin(uint32 roundNum) { }

    void DoAction()
    {
        auto action = GetRoundAction();
        
        action->BeforeDoAction();
        action->DoAction();
        action->AfterDoAction();
    }

    virtual void OnRoundFinished() { }

protected:
    virtual TSharedRef<IRoundAction> GetRoundAction() = 0;
};
