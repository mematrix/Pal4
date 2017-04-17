#pragma once

#include <functional>

#include <Util/TypeTraitsUtil.h>


template<typename T>
class FakeDynamicDelegate;

template<typename Ret, typename T, typename... Args>
class FakeDynamicDelegate<Ret(T::*)(Args...)>
{
public:
    typedef Ret(T::*TMem)(Args...);
    typedef std::function<void(T&, typename pal4::param<Args>::type...)> FPreFunc;
    typedef std::function<Ret(T&, typename pal4::param<Ret>::type, typename pal4::param<Args>::type...)> FPostFunc;

private:
    TMem MemFunc;
    FPreFunc PreFunc;
    FPostFunc PostFunc;

public:
    // 支持隐式转换
    FakeDynamicDelegate(TMem func) : MemFunc(func), PreFunc(nullptr), PostFunc(nullptr) { }
    constexpr FakeDynamicDelegate(nullptr_t) : MemFunc(nullptr) { }
    FakeDynamicDelegate(TMem func, const FPreFunc& pre, const FPostFunc& post) :
        MemFunc(func),
        PreFunc(pre),
        PostFunc(post)
    {
    }
    FakeDynamicDelegate(const FakeDynamicDelegate&) = default;

    FakeDynamicDelegate& operator=(const FakeDynamicDelegate&) = default;

    operator bool() const
    {
        return nullptr != MemFunc;
    }

    Ret operator()(T& obj, typename pal4::param<Args>::type... args)
    {
        if (nullptr == MemFunc)
        {
            throw std::bad_function_call();
        }

        if (PreFunc)
        {
            PreFunc(obj, args);
        }

        if (!PostFunc)
        {
            return obj.*MemFunc(args);
        }
        return PostFunc(obj, obj.*MemFunc(args), args);
    }

    TMem Target() const
    {
        return MemFunc;
    }

    FPreFunc& PreFunction() { return PreFunc; }
    const FPreFunc& PreFunction() const { return PreFunc; }

    FPostFunc& PostFunction() { return PostFunc; }
    const FPostFunc& PostFunction() const { return PostFunc; }
};


template<typename T, typename... Args>
class FakeDynamicDelegate<void(T::*)(Args...)>
{
public:
    typedef void(T::*TMem)(Args...);
    typedef std::function<void(T&, typename pal4::param<Args>::type...)> FPreFunc;
    typedef std::function<void(T&, typename pal4::param<Args>::type...)> FPostFunc;

private:
    TMem MemFunc;
    FPreFunc PreFunc;
    FPostFunc PostFunc;

public:
    // 支持隐式转换
    FakeDynamicDelegate(TMem func) : MemFunc(func), PreFunc(nullptr), PostFunc(nullptr) { }
    constexpr FakeDynamicDelegate(nullptr_t) : MemFunc(nullptr) { }
    FakeDynamicDelegate(TMem func, const FPreFunc& pre, const FPostFunc& post) :
        MemFunc(func),
        PreFunc(pre),
        PostFunc(post)
    {
    }
    FakeDynamicDelegate(const FakeDynamicDelegate&) = default;

    FakeDynamicDelegate& operator=(const FakeDynamicDelegate&) = default;

    operator bool() const
    {
        return nullptr != MemFunc;
    }

    void operator()(T& obj, typename pal4::param<Args>::type... args)
    {
        if (nullptr != MemFunc)
        {
            throw std::bad_function_call();
        }

        if (PreFunc)
        {
            PreFunc(obj, args);
        }

        obj.*MemFunc(args);

        if (PostFunc)
        {
            PostFunc(obj, args);
        }
    }

    TMem Target() const
    {
        return MemFunc;
    }

    FPreFunc& PreFunction() { return PreFunc; }
    const FPreFunc& PreFunction() const { return PreFunc; }

    FPostFunc& PostFunction() { return PostFunc; }
    const FPostFunc& PostFunction() const { return PostFunc; }
};
