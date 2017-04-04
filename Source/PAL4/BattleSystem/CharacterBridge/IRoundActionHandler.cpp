// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"
#include "IRoundActionHandler.h"

IRoundActionHandler::IRoundActionHandler(IRoundActionHandler && other) noexcept :
    RoundManager(other.RoundManager)
{
    other.RoundManager = nullptr;
}

IRoundActionHandler & IRoundActionHandler::operator=(IRoundActionHandler &&other) noexcept
{
    SwapManager(other);
    return (*this);
}

