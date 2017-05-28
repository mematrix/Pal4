#pragma once

#include "Combat/Interface/Round/IRoundDispatcher.h"
#include "FCharacterRoundInfo.h"


class PAL4_API FRoundDispatcher : public IRoundDispatcher
{
public:
    FRoundDispatcher() = default;
    FRoundDispatcher(const FRoundDispatcher&) = default;
    FRoundDispatcher(FRoundDispatcher&&) = default;

    FRoundDispatcher& operator=(const FRoundDispatcher&) = default;
    FRoundDispatcher& operator=(FRoundDispatcher&&) = default;

    void Init(const TArray<TSharedRef<ICharacterDelegate>>&) override;

    void OnBattleBegin() override;

    void AddCharacter(const TSharedRef<ICharacterDelegate>&) override;

    ICharacterDelegate& MoveToNext() override;

    void OnBattleFinished() override;

private:
    static int32 GetNextRandomNum();

    // 刷新UI上的进度条。在角色数量发生变化（如加入新角色到战场、角色死亡或复活）时调用
    void UpdateProgressView();

    void OnCharacterDead(const ICharacterProperty&);
    void OnCharacterRevive(const ICharacterProperty&);

public:
    constexpr static int32 GetMinInitPosition() { return 10; }
    constexpr static int32 GetMaxInitPosition() { return 65; }

private:
    TArray<FCharacterRoundInfo> RoundInfoArray;
};

