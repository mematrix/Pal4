#pragma once

#include <Platform.h>
#include <Delegate.h>

#include "CharacterPrimitives/Model/ECharacterBasicType.h"

class PAL4_API ICharacterPropertyManager
{
public:
    DECLARE_EVENT_TwoParams(ICharacterPropertyManager, FOnPropertyChangedEvent, const ICharacterPropertyManager&, ECharacterBasicType)
    DECLARE_EVENT_OneParam(ICharacterPropertyManager, FOnCharacterDeadEvent, const ICharacterPropertyManager&)
    DECLARE_EVENT_OneParam(ICharacterPropertyManager, FOnCharacterReviveEvent, const ICharacterPropertyManager&)

protected:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnCharacterDeadEvent OnCharacterDeadEvent;
    FOnCharacterReviveEvent OnCharacterReviveEvent;

public:
    ICharacterPropertyManager() = default;
    ICharacterPropertyManager(const ICharacterPropertyManager&) = default;
    ICharacterPropertyManager(ICharacterPropertyManager&&) = default;

    virtual ~ICharacterPropertyManager() { }

    ICharacterPropertyManager& operator=(const ICharacterPropertyManager&) = default;
    ICharacterPropertyManager& operator=(ICharacterPropertyManager&&) = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnCharacterDeadEvent& OnCharacterDead() { return OnCharacterDeadEvent; }
    FOnCharacterReviveEvent& OnCharacterRevive() { return OnCharacterReviveEvent; }

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
     * @return ʵ�����ӻ���ٵ�����ֵ
     */
    virtual int32 AddHealthValue(int32) = 0;
    /**
     * ���ӻ���ٽ�ɫ������ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     * @return ʵ�����ӻ���ٵ�������ֵ
     */
    virtual int32 AddManaValue(int32) = 0;
    /**
     * ���ӻ���ٽ�ɫ������ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     * @return ʵ�����ӻ���ٵ�������ֵ
     */
    virtual int32 AddCraftValue(int32) = 0;

    /**
     * ��ȡָ�������������Ե���
     * @return ָ��ϵ���������Ե���
     */
    virtual int32 GetMagicPoint(EMagicCategory) = 0;
};

