#pragma once


/**
 * 技能释放来源。一个技能可以由道具、特技、仙术、装备注灵等触发
 */
enum class ESkillSource
{
    // 普通攻击
    Physical,
    // 特技
    Stunt,
    // 道具
    Prop,
    // 锻造、注灵
    Prescription,
    // 水系仙术
    WaterMagic,
    // 火系仙术
    FireMagic,
    // 雷系仙术
    ThunderMagic,
    // 风系仙术
    WindMagic,
    // 土系仙术
    SoilMagic,
    // 触发技能
    Trigger
};


/**
 * 技能所属类别。攻击辅助恢复等
 */
enum class ESkillCategory
{
    // 攻击
    Attack,
    // 辅助
    Auxiliary,
    // 恢复
    Restore,
    // 被动
    Reactive,
    // 召唤
    Calling,
    // 复活
    Resurrection,
    // 不可用
    Unavailable
};
