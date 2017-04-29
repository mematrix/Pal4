#pragma once


/**
 * 基本属性类型。等级、经验、精气神、五灵
 */
enum class PAL4_API ECharacterBasicType
{
    Level,
    Experience,
    MaxHealth,
    MaxMana,
    MaxCraft,
    Health,
    Mana,
    Craft,
    WaterPoint,
    FirePoint,
    ThunderPoint,
    WindPoint,
    SoilPoint
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
