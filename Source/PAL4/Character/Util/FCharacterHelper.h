#pragma once

#include "Character/ICharacterProperty.h"
#include "Primitives/EnumType/EWuLing.h"


class PAL4_API FCharacterHelper
{
public:
    /**
     * 角色是否存活
     */
    static bool IsAlive(ICharacterProperty& character)
    {
        return 0 != character.GetBasicInfo(ECharacterBasicType::Health);
    }

    /**
     * 获取指定类别的仙术属性点数
     * @return 指定系仙术的属性点数
     */
    static int32 GetMagicPoint(ICharacterProperty& character, EWuLing ling)
    {
        return character.GetBasicInfo().MagicPoints[static_cast<int32>(ling)];
    }

    /**
     * 增加或减少角色生命值。值为正数表示增加，负数表示减少
     * @return 实际增加或减少的生命值
     */
    static int32 AddHealthValue(ICharacterProperty& character, int32 value)
    {
        int32 cur = character.GetBasicInfo().HealthPoint;
        int32 max = character.GetBasicInfo().MaxHealthPoint;
        int32 result = cur + value;
        result = result > max ? max : (result < 0 ? 0 : result);
        character.SetBasicInfo(ECharacterBasicType::Health, result);

        return result - cur;
    }

    /**
     * 增加或减少角色神属性值。值为正数表示增加，负数表示减少
     * @return 实际增加或减少的神属性值
     */
    static int32 AddManaValue(ICharacterProperty& character, int32 value)
    {
        int32 cur = character.GetBasicInfo().ManaPoint;
        int32 max = character.GetBasicInfo().MaxManaPoint;
        int32 result = cur + value;
        result = result > max ? max : (result < 0 ? 0 : result);
        character.SetBasicInfo(ECharacterBasicType::Mana, result);

        return result - cur;
    }

    /**
     * 增加或减少角色气属性值。值为正数表示增加，负数表示减少
     * @return 实际增加或减少的气属性值
     */
    static int32 AddCraftValue(ICharacterProperty& character, int32 value)
    {
        int32 cur = character.GetBasicInfo().CraftPoint;
        int32 max = character.GetBasicInfo().MaxCraftPoint;
        int32 result = cur + value;
        result = result > max ? max : (result < 0 ? 0 : result);
        character.SetBasicInfo(ECharacterBasicType::Craft, result);

        return result - cur;
    }
};
