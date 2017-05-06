#pragma once

#include "ICharacterProperty.h"
#include "../EnumType/ERole.h"


/**
 * �������Ի���
 */
class PAL4_API IRoleProperty : public ICharacterProperty
{
protected:
    IRoleProperty(const FCharacterBasicInfo&, int32[4]);
    IRoleProperty(const IRoleProperty&) = default;
    IRoleProperty(IRoleProperty&&) = default;

    IRoleProperty& operator=(const IRoleProperty&) = default;
    IRoleProperty& operator=(IRoleProperty&&) = default;

public:
    bool IsDebuffImmune(EImmune) const override final { return false; }

    void SetRoleFavor(ERole, int32);

    void AddRoleFavor(ERole, int32);

    int32 GetRoleFavor(ERole) const;

private:
    // ����Ӻøж�
    int32 FavorOfTianhe;
    // ����ɴ�øж�
    int32 FavorOfLingsha;
    // �������øж�
    int32 FavorOfMengli;
    // ����Ӣ�øж�
    int32 FavorOfZiying;
};
