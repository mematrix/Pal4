#pragma once


/**
 * ������Ϣö�١�������߿��ң��嶾����Ѫ����������
 */
enum class PAL4_API EImmune
{
    // ������
    Root = 1 << 12,
    // ������
    SealMagic = 1 << 11,
    // ������
    BanProp = 1 << 10,
    // ������
    Sleep = 1 << 9,
    // ������
    Crazy = 1 << 8,
    // ������
    Chaos = 1 << 7,

    // ˮ������
    Water = 1 << 6,
    // ������
    Fire = 1 << 5,
    // �׶�����
    Thunder = 1 << 4,
    // �綾����
    Wind = 1 << 3,
    // ��������
    Soil = 1 << 2,

    // ��Ѫ����
    SuckBlook = 1 << 1,
    // ��������
    Death = 1 << 0
};
