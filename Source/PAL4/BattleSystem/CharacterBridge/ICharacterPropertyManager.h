#pragma once

#include <Platform.h>

class PAL4_API ICharacterPropertyManager
{
public:
    virtual ~ICharacterPropertyManager() { }

    /**
     * ��ɫ�Ƿ�������ҿ��Ƶ�һ����true��ʾ���һ����false��ʾ�з�����AI���
     */
    virtual bool IsPlayer() const = 0;
    /**
     * ��ɫ�Ƿ���
     */
    virtual bool IsAlive() const = 0;
    /**
     * ��ȡ��ɫ�ٶ�ֵ
     */
    virtual int32 GetSpeedValue() const = 0;
};
