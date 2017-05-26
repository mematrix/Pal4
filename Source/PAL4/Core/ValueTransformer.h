#pragma once

#include <list>
#include <functional>
#include <algorithm>

#include "Util/TypeTraitsUtil.h"


/**
 * 针对一组值，提供带分组的变换功能。f(x)=sum(f(y)) if y==x
 * @warning 当前只推荐使用简单类型作为KeyType和GroupType
 */
template<typename _KeyType, typename _GroupType, typename Ret, typename... Params>
class PAL4_API ValueTransformer
{
    static_assert(!std::is_same<Ret, void>::value, "return type must not be void!");

public:
    typedef typename pal4::param<_KeyType>::type KeyType;
    typedef typename pal4::param<_GroupType>::type GroupType;

private:
    // TODO: 根据KeyType和GroupType是否为简单类型来决定传参是引用方式还是值方式
    struct PAL4_API Node
    {
        KeyType Key;
        GroupType Group;
        std::function<Ret(Params...)> Func;

        Node(KeyType key, GroupType group, const std::function<Ret(Params...)>& func) :
            Key(key),
            Group(group),
            Func(func)
        {
        }

        Node(const Node&) = default;
        Node(Node&&) = default;
        Node& operator=(const Node&) = default;
        Node& operator=(Node&&) = default;
    };

public:
    ValueTransformer() = default;
    ValueTransformer(const ValueTransformer&) = default;
    ValueTransformer(ValueTransformer&&) = default;
    ValueTransformer& operator=(const ValueTransformer&) = default;
    ValueTransformer& operator=(ValueTransformer&&) = default;

    void AddTransformer(KeyType key, GroupType group, const std::function<Ret(Params...)>& func)
    {
        Transformers.emplace_back(key, group, func);
    }

    void RemoveTransformer(KeyType key, GroupType group)
    {
        Transformers.remove_if([key, group](const Node& node)
        {
            return key == node.Key && group == node.Group;
        });
    }

    void RemoveKey(KeyType key)
    {
        Transformers.remove_if([key](const Node& node)
        {
            return key == node.Key;
        });
    }

    void RemoveGroup(GroupType group)
    {
        Transformers.remove_if([group](const Node& node)
        {
            return group == node.Group;
        });
    }

    template<typename Function>
    void Traverse(Function fn) const
    {
        std::for_each(Transformers.begin(), Transformers.end(), [&fn](const Node& node)
        {
            fn(node.Key, node.Group, node.Func);
        });
    }

    template<typename Function>
    void TraverseByGroup(GroupType group, Function fn) const
    {
        std::for_each(Transformers.begin(), Transformers.end(), [group, &fn](const Node& node)
        {
            if (group == node.Group)
            {
                fn(node.Key, node.Group, node.Func);
            }
        });
    }

    Ret AccumulateByGroup(Ret init, GroupType group, Params... params) const
    {
        for (const Node& node : Transformers)
        {
            if (group == node.Group)
            {
                init = init + node.Func(node.Key, node.Group, params...);
            }
        }

        return init;
    }

private:
    std::list<Node> Transformers;
};
