// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Array.h>
#include <SharedPointer.h>
#include "IBattleStatus.h"

/**
 * 
 */
class PAL4_API FBattleSystem
{
public:
	FBattleSystem(TArray<TSharedRef<IBattleStatus>>);
    FBattleSystem(const FBattleSystem&) = delete;
	~FBattleSystem();

    FBattleSystem& operator=(const FBattleSystem&) = delete;

private:
    TArray<TSharedRef<IBattleStatus>> Characters;
};
