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
    /*
     * ��ȡ��ɫΨһID�����ڴ�ȫ�����ݼ��л�ȡ��ɫ��Ϣ������ͷ�����Ƶ�
     */
    virtual int32 GetId() const = 0;

    /**
     * ��ȡ��ɫ����ֵ
     */
    virtual int32 GetHealthValue() const = 0;
    /**
     * ��ȡ��ɫ�����Ե�ֵ
     */
    virtual int32 GetManaValue() const = 0;
    /**
     * ��ȡ��ɫ�����Ե�ֵ
     */
    virtual int32 GetCraftValue() const = 0;

    /**
     * ���ӻ���ٽ�ɫ����ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     */
    virtual void AddHealthValue(int32) = 0;
    /**
     * ���ӻ���ٽ�ɫ������ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     */
    virtual void AddManaValue(int32) = 0;
    /**
     * ���ӻ���ٽ�ɫ������ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     */
    virtual void AddCraftValue(int32) = 0;
};
