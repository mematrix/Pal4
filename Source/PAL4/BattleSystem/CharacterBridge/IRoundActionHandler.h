// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Platform.h>

/**
 * ����غ϶����Ļص��ӿڡ�ÿ��ֻ�ܰ󶨵���@see FCharacterRoundManager���󶨵�����ҽ�ɫ��AI��ɫ
 */
class PAL4_API IRoundActionHandler
{
public:
	virtual ~IRoundActionHandler() { }

    // virtual void WaitingAct() { }

    virtual void OnNewRoundBegin(uint32 roundNum) { }

    virtual void OnAction() = 0;

    virtual void OnRoundFinished() { }
};
