#pragma once

#include <Platform.h>

// 获取一个整数中比特值为1的最小位置索引，例如0x01的索引为0，0x06的索引为2。
// 如果输入整数值为0，则返回-1。
// 仅建议在计算常数表达式时使用，如果需要计算变量，可使用更优化的方式。
constexpr int32 GetLowBitIndex(int32 i)
{
    return i == 0 ? -1 : (i & 0x01 ? 0 : GetLowBitIndex(i >> 1) + 1);
}

template<typename T>
constexpr int32 GetLowBitIndex(T prop)
{
    return GetLowBitIndex(static_cast<int32>(prop));
}

// 将一个值所有比特位为1的位置置为0，除了索引最小的那个位置。
// TODO: 此方法来源于网上，以后补上来源位置，尽量附上原始来源。
constexpr int32 LowBit(int32 x)
{
    // 原理：对一个整数取负，将保留这个整数中最低“1”比特位以及右边所有0位内容不变，而将其前面所有位取反，
    // 因此进行按位与操作之后，就会将高位所有位都置零，仅保留最低1比特位（其右边的值一直为0）
    return x & -x;
}

template<typename T>
constexpr T LowBit(T x)
{
    return static_cast<T>(LowBit(static_cast<int32>(x)));
}

// 将最低的bit1位置零，其它不变。原理类似上面 @see LowBit
constexpr int32 ResetLowBit(int32 x)
{
    return x & (x - 1);
}

// 常规形式计算最低bit1位的索引。适用于变量。
// TODO：可以与汇编形式（bsf）对比一下实际运行平均速度
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
