#pragma once


/**
 * �����������͡��ȼ������顢����������
 */
enum class PAL4_API ECharacterBasicType
{
    Level = 1 << 0,
    Experience = 1 << 1,
    MaxHealth = 1 << 2,
    MaxMana = 1 << 3,
    MaxCraft = 1 << 4,
    Health = 1 << 5,
    Mana = 1 << 6,
    Craft = 1 << 7,
    WaterPoint = 1 << 8,
    FirePoint = 1 << 9,
    ThunderPoint = 1 << 10,
    WindPoint = 1 << 11,
    SoilPoint = 1 << 12
};

/**
 * �������ࡣˮ���׷���
 */
enum class PAL4_API EMagicCategory
{
    Water,
    Fire,
    Thunder,
    Wind,
    Soil
};
