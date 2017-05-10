#pragma once


/**
 * ���ܴ�������
 */
enum class PAL4_API ESkillTrigerType
{
    // ����������
    HitByMagic,
    // ��Ч��
    EffectAnyTime,
    // ����
    Invoke,
    // ����ͨ��������
    HitByPhysicalAttack,
    // ��ͨ����Ŀ��󴥷�
    HitTarget,
    // ͬ����������
    CompanionsReduced,
    // ÿ�غϴ���
    EachRound,
    // ��ˮϵ��������
    HitByWaterMagic,
    // ����ϵ��������
    HitByFireMagic,
    // ����ϵ��������
    HitByThunderMagic,
    // ����ϵ��������
    HitByWindMagic,
    // ����ϵ��������
    HitBySoilMagic,
    // �����к󣬶Թ�����
    BeHitThenToActor,
    // ����Ŀ��󣬶��Լ�
    HitTargetThenToSelf,
    // ��ͨ�����ж�����ʱ�����Լ�
    PhysicalAttackFinishThenToSelf
};
