#pragma once

#include "ICharacterProperty.h"
#include "Primitives/EnumType/ERole.h"


/**
 * �������Ի���
 */
class PAL4_API IRoleProperty : public ICharacterProperty
{
protected:
    IRoleProperty(const FCharacterBasicInfo&, uint32, uint8 initMagicPoint);
    IRoleProperty(const IRoleProperty&) = default;
    IRoleProperty(IRoleProperty&&) = default;

    IRoleProperty& operator=(const IRoleProperty&) = default;
    IRoleProperty& operator=(IRoleProperty&&) = default;

public:
    bool IsDebuffImmune(EImmune) const override final { return false; }

    void SetRoleFavor(ERole, uint8);

    void AddRoleFavor(ERole, uint8);

    uint8 GetRoleFavor(ERole) const;

    uint8 GetInitMagicPoint() const { return InitMagicPoint; }

private:
    // ����Ӻøж�
    uint8 FavorOfTianhe;
    // ����ɴ�øж�
    uint8 FavorOfLingsha;
    // �������øж�
    uint8 FavorOfMengli;
    // ����Ӣ�øж�
    uint8 FavorOfZiying;
    // ��ʼ�����������0�������������ɫ��ǰ���������=�ȼ�+��ʼ���������
    uint8 InitMagicPoint;
};
