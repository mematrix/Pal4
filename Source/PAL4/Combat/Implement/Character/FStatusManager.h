#pragma once

#include <Map.h>
#include <SharedPointer.h>

#include "Combat/Interface/Character/IStatusManager.h"
#include "FTemporaryStatus.h"

class FCombatCharacter;
class ICharacterDelegate;
class IRoundManager;
class ITempStatusOpWrapper;


class PAL4_API FStatusManager : public IStatusManager
{
public:
    explicit FStatusManager(FCombatCharacter&);

    FStatusManager(const FStatusManager&) = default;
    FStatusManager(FStatusManager&&) = default;
    
    FStatusManager& operator=(const FStatusManager&) = default;
    FStatusManager& operator=(FStatusManager&&) = default;

    const FTemporaryStatus& GetTempStatus() const override { return TempStatus; }

    void SetStatusTransform(int32 skillID, ECharacterStatusType type, uint32 validNum, const std::function<int32(int32)>& func) override;

    void ClearSkillStatus(int32 skillID) override;

    void ClearSpecialStatus(ECharacterStatusType type) override;

    void ClearStatus(int32 skillID, ECharacterStatusType type) override;

    void SetBuff(EBuff buff, uint32 maxRoundNum) override;

    void SetPoison(EPoison poison, uint32 maxRoundNum) override;

    void SetDebuff(EDebuff debuff, uint32 maxRoundNum) override;

    void SetResurrect(bool canResurrct, uint32 maxRoundNum) override;

    void SetInvisible(bool invisible, uint32 maxRoundNum) override;

private:
    FCombatCharacter& Character;
    FTemporaryStatus TempStatus;
    TMap<int32, TSharedRef<ITempStatusOpWrapper>> StatusMap;
};
