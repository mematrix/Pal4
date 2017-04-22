// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <SharedPointer.h>

#include "IRoundAction.h"


/**
 * ����غ϶����Ļص��ӿڡ�ÿ��ֻ�ܰ󶨵���@see FCharacterRoundManager���󶨵�����ҽ�ɫ��AI��ɫ
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
