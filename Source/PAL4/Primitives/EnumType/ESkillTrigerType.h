#pragma once


/**
 * 技能触发条件
 */
enum class PAL4_API ESkillTrigerType
{
    // 被仙术击中
    HitByMagic,
    // 常效型
    EffectAnyTime,
    // 调用
    Invoke,
    // 被普通攻击击中
    HitByPhysicalAttack,
    // 普通击中目标后触发
    HitTarget,
    // 同伴数量减少
    CompanionsReduced,
    // 每回合触发
    EachRound,
    // 被水系仙术击中
    HitByWaterMagic,
    // 被火系仙术击中
    HitByFireMagic,
    // 被雷系仙术击中
    HitByThunderMagic,
    // 被风系仙术击中
    HitByWindMagic,
    // 被土系仙术击中
    HitBySoilMagic,
    // 被命中后，对攻击方
    BeHitThenToActor,
    // 击中目标后，对自己
    HitTargetThenToSelf,
    // 普通攻击行动结束时，对自己
    PhysicalAttackFinishThenToSelf
};
