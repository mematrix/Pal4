#pragma once


template<typename T>
class PAL4_API IEnumerator
{
public:
    virtual ~IEnumerator() = default;
    
    virtual bool MoveNext() = 0;

    virtual T& Current() const = 0;
};
