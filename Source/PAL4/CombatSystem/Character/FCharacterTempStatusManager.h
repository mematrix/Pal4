#pragma once

#include <Map.h>
#include <SharedPointer.h>

#include "CombatDelegate/Character/ICharacterTempStatusAccessor.h"
#include "CombatDelegate/StatusOpWrapper/ICharacterTempStatusOperator.h"
#include "FCharacterTemporaryStatus.h"

class FCombatCharacter;
class ICharacterCombatDelegate;
class ICharacterRoundManager;
class ITempStatusOpWrapper;


class PAL4_API FCharacterTempStatusManager : public ICharacterTempStatusAccessor, public ICharacterTempStatusOperator
{
public:
    explicit FCharacterTempStatusManager(ICharacterCombatDelegate&);

    MAKE_DEFAULT_COPY_MOVE_CTOR_AND_OP(FCharacterTempStatusManager)

    ICharacterCombatDelegate& GetCharacter() { return Character; }
    const ICharacterCombatDelegate& GetCharacter() const { return Character; }

    ICharacterRoundManager& GetRoundManager() override;
    inline const ICharacterRoundManager& GetRoundManager() const;

    void AddTemporaryStatus(ECharacterStatusType, const TSharedRef<ITempStatusOpWrapper>&) override;

    void RemoveTemporaryStatus(ECharacterStatusType, ITempStatusOpWrapper&) override;

    void AddTransformer(void*, ECharacterStatusType, const FTransformAction&) override;

    void RemoveTransformer(void* key, ECharacterStatusType type) override;

    void SetCommonBuffStatus(ECommonBuff value) override;

    void SetPoisonStatus(EPoison value) override;

    void SetControlledDebuffStatus(EControlledDebuff value) override;

    void SetInVisibleStatus(bool value) override;

    void SetReviveStatus(bool value) override;

    const FCharacterBattleStatus& GetBattleStatus() const override;

    int32 GetPropertyValue(ECharacterStatusType type) const override;

    const FCharacterStatusInfo& GetAccumulatedInfo() const override;

private:
    ICharacterCombatDelegate& Character;
    FCharacterTemporaryStatus TempStatus;
    TMap<int32, TSharedRef<ITempStatusOpWrapper>> StatusMap;
};
