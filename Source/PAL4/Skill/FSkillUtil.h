#pragma once

#include "ISkill.h"
#include "Enum/ESkillAttribute.h"


/**
 * һ�������࣬����ִ��һ�μ��ܣ�����������ܸ���������ִ�����񡣸������񳣼��ڸ��Ӽ��ܡ��������������ܵȣ�
 * ����@code ESkillTriggerType \endcode �������Ĵ�������
 */
class PAL4_API FSkillUtil
{
public:
    /**
     * ִ��ָ���ļ��ܡ������ݹ�ִ�м��ܸ�������
     * @param skill Ҫִ�еļ���
     */
    static void Execute(ISkill& skill);


    constexpr static unsigned int MakeSkillAttribute(ESkillSource source, ESkillCategory category)
    {
        return (static_cast<unsigned>(category) << 16) | static_cast<unsigned>(source);
    }

    constexpr static ESkillSource GetSkillSource(unsigned int attribute)
    {
        return static_cast<ESkillSource>(attribute & 0xff);
    }

    constexpr static ESkillCategory GetSkillCategory(unsigned int attribute)
    {
        return static_cast<ESkillCategory>((attribute >> 16) & 0xff);
    }

    static ESkillSource GetSource(const ISkill& skill)
    {
        return GetSkillSource(skill.GetAttribute());
    }

    static ESkillCategory GetCategory(const ISkill& skill)
    {
        return GetSkillCategory(skill.GetAttribute());
    }

    static bool CheckSource(const ISkill& skill, ESkillSource source)
    {
        return GetSource(skill) == source;
    }

    static bool CheckCategory(const ISkill& skill, ESkillCategory category)
    {
        return GetCategory(skill) == category;
    }
};
