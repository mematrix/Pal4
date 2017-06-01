#pragma once


/**
 * 技能触发条件
 */
enum class PAL4_API ESkillTriggerType
{
    // 被仙术击中
    HitByMagic,
    // 常效型
    EffectAnyTime,
    // 调用
    Invoke,
    // 被普通攻击击中，对自身
    HitByPhysicalAttack,
    // 普通攻击击中目标后触发，对目标
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
    // 普通攻击击中目标后，对自己
    HitTargetThenToSelf,
    // 普通攻击行动结束时，对自己
    PhysicalAttackFinishThenToSelf
};


enum class PAL4_API ESkillAttackType
{
    // 物理攻击
    Physical,
    // 水系仙术攻击
    WaterMagic,
    // 火系仙术攻击
    FireMagic,
    // 雷系仙术攻击
    ThunderMagic,
    // 风系仙术攻击
    WindMagic,
    // 土系仙术攻击
    SoilMagic,
    // 特技攻击
    Stunt,
    // 道具攻击
    Prop
};


enum class PAL4_API ESkillTriggerTarget
{
    // 攻击者触发，对自身
    ActorToSelf,
    // 攻击者触发，对被攻击目标
    ActorToPeer,
    // 被攻击者触发，对自身
    TargetToSelf,
    // 被攻击者触发，对攻击者
    TargetToPeer
};
