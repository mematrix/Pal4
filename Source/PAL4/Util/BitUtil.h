#pragma once

#include <Platform.h>

// ��ȡһ�������б���ֵΪ1����Сλ������������0x01������Ϊ0��0x06������Ϊ2��
// �����������ֵΪ0���򷵻�-1��
// �������ڼ��㳣�����ʽʱʹ�ã������Ҫ�����������ʹ�ø��Ż��ķ�ʽ��
constexpr int32 GetLowBitIndex(int32 i)
{
    return i == 0 ? -1 : (i & 0x01 ? 0 : GetLowBitIndex(i >> 1) + 1);
}

template<typename T>
constexpr int32 GetLowBitIndex(T prop)
{
    return GetLowBitIndex(static_cast<int32>(prop));
}

// ��һ��ֵ���б���λΪ1��λ����Ϊ0������������С���Ǹ�λ�á�
// TODO: �˷�����Դ�����ϣ��Ժ�����Դλ�ã���������ԭʼ��Դ��
constexpr int32 LowBit(int32 x)
{
    // ԭ����һ������ȡ���������������������͡�1������λ�Լ��ұ�����0λ���ݲ��䣬������ǰ������λȡ����
    // ��˽��а�λ�����֮�󣬾ͻὫ��λ����λ�����㣬���������1����λ�����ұߵ�ֵһֱΪ0��
    return x & -x;
}

template<typename T>
constexpr T LowBit(T x)
{
    return static_cast<T>(LowBit(static_cast<int32>(x)));
}

// ����͵�bit1λ���㣬�������䡣ԭ���������� @see LowBit
constexpr int32 ResetLowBit(int32 x)
{
    return x & (x - 1);
}

// ������ʽ�������bit1λ�������������ڱ�����
// TODO������������ʽ��bsf���Ա�һ��ʵ������ƽ���ٶ�
inline int32 LowBitIndex(uint32 x)
{
    if (0 == x) return -1;

    int32 n = 1;
    if (0 == (x & 0x0000ffff))
    {
        n += 16;
        x >>= 16;
    }
    if (0 == (x & 0x000000ff))
    {
        n += 8;
        x >>= 8;
    }
    if (0 == (x & 0x0000000f))
    {
        n += 4;
        x >>= 4;
    }
    if (0 == (x & 0x00000003))
    {
        n += 2;
        x >>= 2;
    }

    return n - (x & 1);
}
