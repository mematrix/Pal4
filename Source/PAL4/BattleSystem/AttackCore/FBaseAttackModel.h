#pragma once

/**
 * ��������ģ�ͻ��ࡣ�洢һ�ι���������������ݣ����ݹ������Ͳ�ͬ�����໯��Ӧ��ģ����
 * @warning �������Ϊ��̬����Ϊ���ݽṹ��ơ��̳��뿼��ʹ��private����protected�̳�
 */
class PAL4_API FBaseAttackModel
{
protected:
    FBaseAttackModel() = default;
    FBaseAttackModel(const FBaseAttackModel&) = default;
    FBaseAttackModel& operator=(const FBaseAttackModel&) = default;

    ~FBaseAttackModel() = default;
};
