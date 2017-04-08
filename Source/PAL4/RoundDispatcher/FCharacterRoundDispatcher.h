#pragma once

#include "BattleSystem/RoundDispatcher/ICharacterRoundDispatcher.h"
#include "FCharacterRoundInfo.h"


class PAL4_API FCharacterRoundDispatcher : public ICharacterRoundDispatcher
{
public:
    FCharacterRoundDispatcher() = default;
    FCharacterRoundDispatcher(const FCharacterRoundDispatcher&) = default;
    FCharacterRoundDispatcher(FCharacterRoundDispatcher&&) = default;

    FCharacterRoundDispatcher& operator=(const FCharacterRoundDispatcher&) = default;
    FCharacterRoundDispatcher& operator=(FCharacterRoundDispatcher&&) = default;

    void OnBattleBegin(const TArray<TSharedRef<FBattleCharacter>>&) override;

    void AddCharacter(const TSharedRef<FBattleCharacter>&) override;

    FBattleCharacter& MoveToNext() override;

    void OnBattleFinished() override;

private:
    static int32 GetNextRandomNum();

    // 刷新UI上的进度条。在角色数量发生变化（如加入新角色到战场、角色死亡或复活）时调用
    void UpdateProgressView();

    void OnCharacterDead(const ICharacterBattleDelegate&);
    void OnCharacterRevive(const ICharacterBattleDelegate&);

public:
    constexpr static int32 GetMinInitPosition() { return 10; }
    constexpr static int32 GetMaxInitPosition() { return 65; }

private:
    TArray<FCharacterRoundInfo> RoundInfoArray;
};

