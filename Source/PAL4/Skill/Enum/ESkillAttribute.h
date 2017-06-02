#pragma once


/**
 * �����ͷ���Դ��һ�����ܿ����ɵ��ߡ��ؼ���������װ��ע��ȴ���
 */
enum class ESkillSource
{
    // ��ͨ����
    PhysicalAttack,
    // �ؼ�
    Stunt,
    // ����
    Prop,
    // ���졢ע��
    Prescription,
    // ˮϵ����
    WaterMagic,
    // ��ϵ����
    FireMagic,
    // ��ϵ����
    ThunderMagic,
    // ��ϵ����
    WindMagic,
    // ��ϵ����
    SoilMagic
    // ������������
    // Trigger
};


/**
 * ����������𡣹��������ָ���
 */
enum class ESkillCategory
{
    // ����
    Attack,
    // ����
    Auxiliary,
    // �ָ�
    Restore,
    // ����
    Reactive,
    // �ٻ�
    Calling,
    // ����
    Resurrection,
    // ������
    Unavailable
};


constexpr unsigned int MakeSkillAttribute(ESkillSource source, ESkillCategory category)
{
    return (static_cast<unsigned>(category) << 16) | static_cast<unsigned>(source);
}

constexpr ESkillSource GetSkillSource(unsigned int attribute)
{
    return static_cast<ESkillSource>(attribute & 0xff);
}

constexpr ESkillCategory GetSkillCategory(unsigned int attribute)
{
    return static_cast<ESkillCategory>((attribute >> 16) & 0xff);
}
