// Fill out your copyright notice in the Description page of Project Settings.

#include "PAL4.h"

#include <mutex>

#include "FCoreGame.h"


static TSharedPtr<FCoreGame> Instance = nullptr;
static std::once_flag InstanceInitFlag;

FCoreGame& FCoreGame::SharedInstance()
{
    std::call_once(InstanceInitFlag, []()
    {
        Instance = MakeShared<FCoreGame>();
    });

    return *Instance;
}

