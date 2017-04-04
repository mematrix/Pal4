#pragma once

enum class PAL4_API ECommonBuff
{
    None = 0,
    // ���������չ����ؼ�
    ReboundAttackAndSkill = 1,
    // �ڣ���ͨ������Ч
    InvalidateAttack = 2,
    // �磬����������Ч
    InvalidateMagic = 3,
    // �������������˺�
    AbsorbMagicDamage = 4
};

enum class PAL4_API EPoison
{
    None = 0,
    // ˮ��
    Water = 1,
    // ��
    Fire = 2,
    // �׶�
    Thunder = 3,
    // �綾
    Wind = 4,
    // ����
    Soil = 5
};

enum class PAL4_API EControlledDebuff
{
    None = 0,
    // ������ɫ�ж���ֹͣ�����ɲ���
    Root = 1,
    // �⣬��ɫ����ʹ������
    SealMagic = 2,
    // ������ɫ����ʹ����Ʒ��������
    BanProp = 3,
    // �ߣ���ɫ�ж���ֹͣ
    Sleep = 4,
    // �񣬽�ɫ�޷����ƣ����ֵ��ҵĽ�����ͨ�������������ӱ�
    Crazy = 5,
    // �ң���ɫ�޷����ƣ����ֵ��ң���ʹ�����⼼�ܡ���Ʒ
    Chaos = 6
};

enum class PAL4_API ECharacterBattleStatus
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
