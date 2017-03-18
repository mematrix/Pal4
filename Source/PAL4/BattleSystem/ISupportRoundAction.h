// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>

/**
 * 
 */
class PAL4_API ISupportRoundAction
{
public:
	virtual ~ISupportRoundAction() { }

    virtual void WaitingAct() { }

    virtual void OnNewRoundBegin(uint32 roundNum) { }

    virtual void OnAction() = 0;

    virtual void OnRoundFinished() { }
};
