#pragma once

#include <mutex>

template<typename... Mutexes>
class _LockGuard_t;

template<typename Mutex1, typename... Mutexes>
class _LockGuard_t : public _LockGuard_t<Mutexes...>
{
    Mutex1& mtx;

public:
    _LockGuard_t(Mutex1& m, Mutexes&... mtxs) : mtx(m), _LockGuard_t<Mutexes...>(mtxs) { }

    _LockGuard_t(const _LockGuard_t&) = delete;

    ~_LockGuard_t()
    {
        mtx.unlock();
    }
};

template<>
class _LockGuard_t<> { };

template<typename Mutex1, typename Mutex2, typename... Mutexes>
class PAL4_API LockGuard : public _LockGuard_t<Mutex2, Mutexes...>
{
    Mutex1& mtx;

public:
    LockGuard(Mutex1& mtx1, Mutex2& mtx2, Mutexes&... mtxs) : 
        _LockGuard_t<Mutex2, Mutexes...>(mtx2, mtxs), 
        mtx(mtx1) 
    {
        std::lock(mtx1, mtx2, mtxs);
    }

    LockGuard(const LockGuard&) = delete;

    ~LockGuard()
    {
        mtx.unlock();
    }
};
