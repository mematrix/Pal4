// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"
#include "ISupportRoundAction.h"

class FDefaultRoundAction : public ISupportRoundAction
{
    void OnAction() override { }
};

static FDefaultRoundAction action;

ISupportRoundAction & GetDefaultRoundAction()
{
    return action;
}
