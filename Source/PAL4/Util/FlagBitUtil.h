#pragma once

#include <Platform.h>

// 获取一个整数中比特值为1的最小位置索引，例如0x01的索引为0，0x06的索引为2。
// 如果输入整数值为0，则返回-1。
// 仅建议在计算常数表达式时使用，如果需要计算变量，可使用更优化的方式。
constexpr int32 GetLeastBitIndex(int32 i)
{
    return i == 0 ? -1 : (i & 0x01 ? 0 : GetLeastBitIndex(i >> 1) + 1);
}

template<typename T>
constexpr int32 GetFlagLeastBitIndex(T prop)
{
    return GetLeastBitIndex(static_cast<int32>(prop));
}

