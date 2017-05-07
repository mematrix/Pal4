#pragma once


// 2017-04-29���£�ʹ��ƴ��������ĵ��ֱ�����˼ʵ�ڲ����ҵ�ƥ�������Ӣ������
enum class PAL4_API ECommonBuff
{
    None = 0,
    // ���������չ����ؼ���ReboundAttackAndSkill
    Jing = 1,
    // �ڣ���ͨ������Ч��InvalidateAttack
    Bi = 2,
    // �磬����������Ч��InvalidateMagic
    Jie = 3,
    // �������������˺���AbsorbMagicDamage
    Ning = 4
};

/**
 * �嶾��
 * ˮ��:����ͷ�������ɫ��
 * ��:����ͷ�������ɫ��
 * ����:����ͷ�������ɫ��
 * �׶�:����ͷ�������ɫ��
 * �綾:����ͷ�������ɫ��
 */
enum class PAL4_API EPoison
{
    None = 0,
    // ˮ����ʹ���κ���������Ʒ���ؼ������޷�ʹ�ж��߻ظ�������
    Water = 1,
    // �𶾡��ж���ÿ�غϼ���һ�������ġ�����
    Fire = 2,
    // �׶����ж��߷�����ͨ����ʱ����������ġ�����
    Thunder = 3,
    // �綾���ж���ÿ�غϼ���һ�������ġ���
    Wind = 4,
    // ������ʹ���κ���Ʒ���޷�ʹ�ж��߻ظ�����
    Soil = 5
};

enum class PAL4_API EControlledDebuff
{
    None = 0,
    // ������ɫ���ڲ��ɲ���״̬
    Root = 1,
    // �⣬��ɫ����ʹ����������Ʒ
    SealMagic = 2,
    // ������ɫ����ʹ����Ʒ���ؼ�������ʹ������
    BanProp = 3,
    // �ߣ���ɫ���ڲ��ɲ���״̬���ܹ����ɽ��
    Sleep = 4,
    // �񣬽�ɫ�޷����ƣ����ֵ��ҵĽ�����ͨ�������������ӱ�
    Crazy = 5,
    // �ң���ɫ�޷����ƣ����ֵ��ң�����ս���г���ʹ����Ʒ�������������
    Chaos = 6
};

enum class PAL4_API ECombatStatus
{
    // ��������
    Property,
    // ͨ��Buff
    CommonBuff,
    // ����״̬
    Invisible,
    // ������״̬
    CanRevive,
    // �ж�����
    Poison,
    // ������Debuff
    ControlledDebuff
};
