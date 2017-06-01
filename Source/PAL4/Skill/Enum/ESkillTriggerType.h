#pragma once


/**
 * ���ܴ�������
 */
enum class PAL4_API ESkillTriggerType
{
    // ����������
    HitByMagic,
    // ��Ч��
    EffectAnyTime,
    // ����
    Invoke,
    // ����ͨ�������У�������
    HitByPhysicalAttack,
    // ��ͨ��������Ŀ��󴥷�����Ŀ��
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
    // ��ͨ��������Ŀ��󣬶��Լ�
    HitTargetThenToSelf,
    // ��ͨ�����ж�����ʱ�����Լ�
    PhysicalAttackFinishThenToSelf
};


enum class PAL4_API ESkillAttackType
{
    // ������
    Physical,
    // ˮϵ��������
    WaterMagic,
    // ��ϵ��������
    FireMagic,
    // ��ϵ��������
    ThunderMagic,
    // ��ϵ��������
    WindMagic,
    // ��ϵ��������
    SoilMagic,
    // �ؼ�����
    Stunt,
    // ���߹���
    Prop
};


enum class PAL4_API ESkillTriggerTarget
{
    // �����ߴ�����������
    ActorToSelf,
    // �����ߴ������Ա�����Ŀ��
    ActorToPeer,
    // �������ߴ�����������
    TargetToSelf,
    // �������ߴ������Թ�����
    TargetToPeer
};
