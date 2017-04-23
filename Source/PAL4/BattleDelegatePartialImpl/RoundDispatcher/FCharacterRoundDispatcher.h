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

    // ˢ��UI�ϵĽ��������ڽ�ɫ���������仯��������½�ɫ��ս������ɫ�����򸴻ʱ����
    void UpdateProgressView();

    void OnCharacterDead(const ICharacterBattleDelegate&);
    void OnCharacterRevive(const ICharacterBattleDelegate&);

public:
    constexpr static int32 GetMinInitPosition() { return 10; }
    constexpr static int32 GetMaxInitPosition() { return 65; }

private:
    TArray<FCharacterRoundInfo> RoundInfoArray;
};

