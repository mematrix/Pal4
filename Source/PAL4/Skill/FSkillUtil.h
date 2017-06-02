#pragma once

#include "ISkill.h"
#include "Enum/ESkillAttribute.h"


/**
 * 一个工具类，用于执行一次技能，包括这个技能附带的所有执行任务。附加任务常见于附加技能、引发的其它技能等；
 * 比如@code ESkillTriggerType \endcode 中描述的触发任务。
 */
class PAL4_API FSkillUtil
{
public:
    /**
     * 执行指定的技能。包括递归执行技能附带技能
     * @param skill 要执行的技能
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
