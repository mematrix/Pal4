#pragma once


enum class PAL4_API EImmune
{
    // ������
    Root = 1 << 0,
    // ������
    SealMagic = 1 << 1,
    // ������
    BanProp = 1 << 2,
    // ������
    Sleep = 1 << 3,
    // ������
    Crazy = 1 << 4,
    // ������
    Chaos = 1 << 5,

    // ˮ������
    Water = 1 << 6,
    // ������
    Fire = 1 << 7,
    // �׶�����
    Thunder = 1 << 8,
    // �綾����
    Wind = 1 << 9,
    // ��������
    Soil = 1 << 10,

    // ��Ѫ����
    SuckBlook = 1 << 11,
    // ��������
    Death = 1 << 12
};
