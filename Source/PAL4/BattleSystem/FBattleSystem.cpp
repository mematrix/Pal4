// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"
#include "FBattleSystem.h"


FBattleSystem::FBattleSystem(TArray<TSharedRef<IBattleStatus>> characters) :
    Characters(MoveTemp(characters))
{
}

FBattleSystem::~FBattleSystem()
{
}
