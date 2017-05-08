#pragma once

#include <string>

#include <Platform.h>


/**
 * ��Ʒ����
 */
struct PAL4_API FPropertyData
{
    // ��ƷID
    int32 ID;
    // ��Ʒ����
    std::string Name;
    // ��Ʒ��Ϣ����
    std::string Description;
    // ��Ʒ����˵��
    std::string EffectDescription;

    // ��Ʒ����
    uint8 Class;
    // ���ߵȼ�
    uint8 Level;
    // Ŀ��
    uint8 Target;
    // AIָ������
    uint8 AICommandType;
    // ����Ƿ����ʹ��
    bool CanUseByTianhe;
    // ��ɴ�Ƿ����ʹ��
    bool CanUseByLingsha;
    // �����Ƿ����ʹ��
    bool CanUseByMengli;
    // ��Ӣ�Ƿ����ʹ��
    bool CanUseByZiying;

    // ��Ǯ�۸�
    int32 Price;
    // ���ؼ���ID
    int32 SkillID;
    // �Ƿ���Զ�������
    bool CanSell;
    // �Ƿ������ϵͳ��ʹ�ã�����ս�����ʹ�ã�
    bool CanUseInSystem;
    // Ͷ������
    uint8 ThrowType;
    // Ч����ʼ����ʱ�䣺0��ʾ���ҷ��غϿ�ʼʱΪ�����ڵ㣬1��ʾ�ҷ��غϽ��������з��غϿ�ʼ��ʱΪ����ڵ�
    uint8 EffectStartTime;

    // ��άͼ��
    int32 IconID2D;
    // ��άģ�ͱ��
    int32 ModelID3D;
    // ��ά��ͼ���
    int32 MapID3D;
};
