#pragma once


/**
 * 基本属性类型。等级、经验、精气神、五灵
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
 * 仙术分类。水火雷风土
 */
enum class PAL4_API EMagicCategory
{
    Water,
    Fire,
    Thunder,
    Wind,
    Soil
};
