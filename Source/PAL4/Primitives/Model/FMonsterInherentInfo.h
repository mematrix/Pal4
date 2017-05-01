#pragma once

#include <NameTypes.h>

#include "../EnumType/EAIType.h"


struct PAL4_API FMonsterInherentInfo
{
    // ������Ϣ����
    FName Description;
    // �Ƿ�Boss
    bool IsBoss;
    // AI��������
    EAIType AIType;
    // ӵ�м����б�0�����޼���
    int32 SkillIDList[6];
    // AI����ʱ����ʹ�ø��ʵ������飬��10000Ϊ��������ٷֱȡ�
    // ����ֵ�ǵ����ǵݼ��ģ���������ֵ����һ������ҿ������䣬���е�һ��ֵ��0���ɼ���1�ĸ��ʡ�
    // ���䲻���ڵ����������[20, 20)������)��ʾ���ܲ��ᱻʹ�ã�Ҳ���Ǽ���IDΪ0�������ڣ���
    // ���һλʼ��Ϊ10000��������ͨ������
    int32 SkillUsingProbability[7];
    // ��͵����ƷID��ע����ƷIDΪ��ǮIDʱ�����͵�Խ�Ǯ��
    // ��Ϊ�ɽ������ݿ���������ʾû�й������ͬʱ͵�Ե���Ǯ����Ʒ����˴˴�����ϲ���
    int32 StealPropID;
    // ͵����Ʒ���������ڽ�Ǯ��˵����͵�Խ�Ǯ��
    int32 StealPropCount;
    // ������ƷID�б�
    int32 DropPropIDList[4];
    // ������Ʒ���ʡ���10000Ϊ��������ٷֱȡ�ÿ����Ʒ���ʶ��Ƕ�����
    int32 DropPropProbability[4];
    // �����Ǯ��Сֵ
    int32 DropMoneyMinValue;
    // �����Ǯ���ֵ
    int32 DropMoneyMaxValue;
    // ����ʼ��ֵ
    int32 CraftInitPoint;
};
