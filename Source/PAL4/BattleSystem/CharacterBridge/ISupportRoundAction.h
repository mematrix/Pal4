// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <utility>
#include <Platform.h>

class FCharacterRoundManager;

/**
 * 
 */
class PAL4_API ISupportRoundAction
{
    friend class FCharacterRoundManager;

public:
    ISupportRoundAction() noexcept : RoundManager(nullptr) { }
    ISupportRoundAction(const ISupportRoundAction&) = delete;
    ISupportRoundAction(ISupportRoundAction&&);

    ISupportRoundAction& operator=(ISupportRoundAction&) = delete;
    ISupportRoundAction& operator=(ISupportRoundAction&&);

    FCharacterRoundManager* GetRoundManager() const { return RoundManager; }

	virtual ~ISupportRoundAction() { }

    // virtual void WaitingAct() { }

    virtual void OnNewRoundBegin(uint32 roundNum) { }

    virtual void OnAction() = 0;

    virtual void OnRoundFinished() { }

private:
    void SwapManager(ISupportRoundAction& other) noexcept
    {
        std::swap(RoundManager, other.RoundManager);
    }

    FCharacterRoundManager *RoundManager;
};

FORCEINLINE ISupportRoundAction& GetDefaultRoundAction();
