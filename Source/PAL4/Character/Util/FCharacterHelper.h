#pragma once

#include "Character/ICharacterProperty.h"
#include "Primitives/EnumType/EWuLing.h"


class PAL4_API FCharacterHelper
{
public:
    /**
     * ��ɫ�Ƿ���
     */
    static bool IsAlive(ICharacterProperty& character)
    {
        return 0 != character.GetBasicInfo(ECharacterBasicType::Health);
    }

    /**
     * ��ȡָ�������������Ե���
     * @return ָ��ϵ���������Ե���
     */
    static int32 GetMagicPoint(ICharacterProperty& character, EWuLing ling)
    {
        return character.GetBasicInfo().MagicPoints[static_cast<int32>(ling)];
    }

    /**
     * ���ӻ���ٽ�ɫ����ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     * @return ʵ�����ӻ���ٵ�����ֵ
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
     * ���ӻ���ٽ�ɫ������ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     * @return ʵ�����ӻ���ٵ�������ֵ
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
     * ���ӻ���ٽ�ɫ������ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     * @return ʵ�����ӻ���ٵ�������ֵ
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
