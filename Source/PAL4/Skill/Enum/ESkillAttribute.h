#pragma once


/**
 * �����ͷ���Դ��һ�����ܿ����ɵ��ߡ��ؼ���������װ��ע��ȴ���
 */
enum class ESkillSource
{
    // ��ͨ����
    Physical,
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
    SoilMagic,
    // ��������
    Trigger
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
