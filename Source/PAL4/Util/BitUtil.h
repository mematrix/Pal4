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
