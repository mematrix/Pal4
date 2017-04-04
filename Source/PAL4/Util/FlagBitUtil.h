#pragma once

#include <Platform.h>

// ��ȡһ�������б���ֵΪ1����Сλ������������0x01������Ϊ0��0x06������Ϊ2��
// �����������ֵΪ0���򷵻�-1��
// �������ڼ��㳣�����ʽʱʹ�ã������Ҫ�����������ʹ�ø��Ż��ķ�ʽ��
constexpr int32 GetLeastBitIndex(int32 i)
{
    return i == 0 ? -1 : (i & 0x01 ? 0 : GetLeastBitIndex(i >> 1) + 1);
}

template<typename T>
constexpr int32 GetFlagLeastBitIndex(T prop)
{
    return GetLeastBitIndex(static_cast<int32>(prop));
}

