// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class PAL4_API FCharacterPropertyManager
{
public:
	FCharacterPropertyManager();
	~FCharacterPropertyManager();

    // ��ɫ�Ƿ�������ҿ��Ƶ�һ����true��ʾ���һ����false��ʾ�з�����AI���
    bool IsPlayer() const;
    // ��ɫ�Ƿ���
    bool IsAlive() const;
};
