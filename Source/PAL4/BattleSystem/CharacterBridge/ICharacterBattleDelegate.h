#pragma once

#include <functional>

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class IRoundActionHandler;
class ICharacterPropertyManager;
class FCharacterPersistentStatus;
class ICharacterRoundManager;
class ICharacterTemporaryStatus;

class ICharacterBattleDelegate;

template<typename Model>
struct PAL4_API ActionResultModel
{
    /**
    * ����ָʾֵ
    */
    int32 Type;
    /**
    * �����ͷ��ߣ������ߣ�
    */
    ICharacterBattleDelegate* Releaser;
    /**
    * ����Ŀ�꣨�������ߣ�
    */
    ICharacterBattleDelegate* Target;
    /**
    * ��������ģ�������
    */
    Model* ActionModel;
    /**
     * �Զ��帽������
     */
    void* Tag;
};

template ActionResultModel<FBaseStatusModel>;
template ActionResultModel<FBaseAttackModel>;
template ActionResultModel<FBaseRestorerModel>;

/*
 * ����ս��������ࡣ��Ϊһ��������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
 * ͬʱ�ṩս����������Ҫ����Ϣ�ͻص����ƽӿ�
 */
class PAL4_API ICharacterBattleDelegate
{
public:
    virtual ~ICharacterBattleDelegate()
    {
    }

    virtual ICharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterPersistentStatus& GetPersistentStatus() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnBattleBegin(const ICharacterRoundManager&, const ICharacterTemporaryStatus&) = 0;

    virtual void OnBattleFinished() = 0;


    /**
    * ���ý�ɫ����ʱ�Ļص���
    * @warning Ŀǰ������ @code ICharacterRoundDispatcher\endcode ��
    */
    virtual void SetOnDeadCallback(std::function<void(const ICharacterBattleDelegate&)>) = 0;
    /**
    * ���ý�ɫ����ʱ�Ļص���
    * @warning Ŀǰ������ @code ICharacterRoundDispatcher\endcode ��
    */
    virtual void SetOnReviveCallback(std::function<void(const ICharacterBattleDelegate&)>) = 0;
};
