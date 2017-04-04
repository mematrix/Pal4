// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"
#include "ISupportRoundAction.h"

ISupportRoundAction::ISupportRoundAction(ISupportRoundAction && other) :
    RoundManager(other.RoundManager)
{
    other.RoundManager = nullptr;
}

ISupportRoundAction & ISupportRoundAction::operator=(ISupportRoundAction &&other)
{
    SwapManager(other);
    return (*this);
}

class FDefaultRoundAction : public ISupportRoundAction
{
    void OnAction() override { }
};

static FDefaultRoundAction action;

ISupportRoundAction & GetDefaultRoundAction()
{
    return action;
}
