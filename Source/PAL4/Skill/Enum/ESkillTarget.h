#pragma once


/**
 * 技能目标
 */
enum class PAL4_API ESkillTarget
{
    // 针对自身
    Self,
    // 我方单体
    SingleOfOwnSide,
    // 敌方单体
    SingleOfEnemy,
    // 我方全体
    AllOfOwnSide,
    // 敌方全体
    AllOfEnemy,
    // 调用时指定
    AppointWhenInvoke
};
