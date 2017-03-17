// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <mutex>
#include <functional>
#include <map>

#include "Util/MutexUtil.h"

/**
 * 
 */
template<typename Key, typename Ret, typename... Args>
class PAL4_API TMultiDelegate
{
public:
	TMultiDelegate() = default;

    TMultiDelegate(const TMultiDelegate& other) : 
        CopyMutex(),
        Delegates((std::lock_guard(other.CopyMutex), other.Delegates)) { }

    TMultiDelegate(TMultiDelegate&& other) :
        CopyMutex(),
        Delegates((std::lock_guard(other.CopyMutex), MoveTemp(other.Delegates))) { }

	~TMultiDelegate() = default;

    TMultiDelegate& operator=(const TMultiDelegate& other)
    {
        LockGuard<std::mutex, std::mutex> guard(CopyMutex, other.CopyMutex);
    }

private:
    std::mutex CopyMutex;
    std::map<Key, std::function<Ret(Args...)>> Delegates;
};
