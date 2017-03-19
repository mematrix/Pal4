#pragma once

#include <algorithm>
#include <deque>

// custom priority queue. main code refers to std::priority_queue provided by MSVC.
// change default Container to std::queue, and add remove node method.
template<typename T,
    typename Container = std::deque<T>,
    typename Compare = std::less<typename Container::value_type> >
    class PAL4_API PriorityQueue
{
    // priority queue implemented with a Container
public:
    typedef PriorityQueue<T, Container, Compare> Myt;
    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

    PriorityQueue() 
        : c(), comp()
    {	// construct with empty container, default comparator
    }

    PriorityQueue(const Myt& right) 
        : c(right.c), comp(right.comp)
    {	// construct by copying right
    }

    explicit PriorityQueue(const Compare& pred) 
        : c(), comp(pred)
    {	// construct with empty container, specified comparator
    }

    PriorityQueue(const Compare& pred, const Container& container) 
        : c(container), comp(pred)
    {	// construct by copying specified container, comparator
        std::make_heap(c.begin(), c.end(), comp);
    }

    template<typename InputIterator>
    PriorityQueue(InputIterator first, InputIterator last) 
        : c(first, last), comp()
    {	// construct by copying [first, last), default comparator
        std::make_heap(c.begin(), c.end(), comp);
    }

    template<typename InputIterator>
    PriorityQueue(InputIterator first, InputIterator last, const Compare& pred) 
        : c(first, last), comp(pred)
    {	// construct by copying [first, last), specified comparator
        std::make_heap(c.begin(), c.end(), comp);
    }

    template<typename InputIterator>
    PriorityQueue(InputIterator first, InputIterator last, const Compare& pred, const Container& container)
        : c(container), comp(pred)
    {	// construct by copying [first, last), container, and comparator
        c.insert(c.end(), first, last);
        std::make_heap(c.begin(), c.end(), comp);
    }

    Myt& operator=(const Myt& right)
    {	// assign by copying right
        c = right.c;
        comp = right.comp;
        return (*this);
    }

    template<typename Alloc,
        typename = typename enable_if<usesAllocator<Container, Alloc>::value, void>::type>
        explicit PriorityQueue(const Alloc& alloc)
        : c(alloc)
    {	// construct with empty container, allocator
    }

    template<typename Alloc,
        typename = typename enable_if<usesAllocator<Container, Alloc>::value, void>::type>
        PriorityQueue(const Compare& pred, const Alloc& alloc)
        : c(alloc), comp(pred)
    {	// construct with empty container, comparator, allocator
    }

    template<typename Alloc,
        typename = typename enable_if<std::uses_allocator usesAllocator<Container, Alloc>::value, void>::type>
        PriorityQueue(const Compare& pred, const Container& container,
            const Alloc& alloc)
        : c(container, alloc), comp(pred)
    {	// construct by copying specified container, comparator, allocator
        std::make_heap(c.begin(), c.end(), comp);
    }

    template<typename Alloc,
        typename = typename enable_if<usesAllocator<Container, Alloc>::value, void>::type>
        PriorityQueue(const Myt& right, const Alloc& alloc)
        : c(right.c, alloc), comp(right.comp)
    {	// construct by copying right, allocator
    }

    PriorityQueue(Myt&& right)
        noexcept(is_nothrow_move_constructible<Container>::value && is_nothrow_move_constructible<Compare>::value)
        : c(std::move(right.c)), comp(std::move(right.comp))
    {	// construct by moving right
    }

    PriorityQueue(const Compare& pred, Container&& container)
        : c(std::move(container)), comp(pred)
    {	// construct by moving specified container, comparator
        std::make_heap(c.begin(), c.end(), comp);
    }

    template<class InputIterator>
    PriorityQueue(InputIterator first, InputIterator last, const Compare& pred, Container&& container)
        : c(std::move(container)), comp(pred)
    {	// construct by copying [first, last), moving container
        c.insert(c.end(), first, last);
        std::make_heap(c.begin(), c.end(), comp);
    }

    template<class Alloc,
        class = typename enable_if<usesAllocator<Container, Alloc>::value,
        void>::type>
        PriorityQueue(const Compare& pred, Container&& container,
            const Alloc& alloc)
        : c(std::move(container), alloc), comp(pred)
    {	// construct by moving specified container, comparator, allocator
        std::make_heap(c.begin(), c.end(), comp);
    }

    template<class Alloc,
        class = typename enable_if<usesAllocator<Container, Alloc>::value,
        void>::type>
        PriorityQueue(Myt&& right, const Alloc& alloc)
        : c(std::move(right.c), alloc), comp(std::move(right.comp))
    {	// construct by moving right, allocator
    }

    Myt& operator=(Myt&& right)
        _NOEXCEPT_OP(is_nothrow_move_assignable<Container>::value
            && is_nothrow_move_assignable<Compare>::value)
    {	// assign by moving right
        c = std::move(right.c);
        comp = std::move(right.comp);
        return (*this);
    }

    void push(value_type&& _Val)
    {	// insert element at beginning
        c.push_back(std::move(_Val));
        push_heap(c.begin(), c.end(), comp);
    }

    template<class... _Valty>
    void emplace(_Valty&&... _Val)
    {	// insert element at beginning
        c.emplace_back(std::forward<_Valty>(_Val)...);
        push_heap(c.begin(), c.end(), comp);
    }


    bool empty() const
    {	// test if queue is empty
        return (c.empty());
    }

    size_type size() const
    {	// return length of queue
        return (c.size());
    }

    const_reference top() const
    {	// return highest-priority element
        return (c.front());
    }

    void push(const value_type& _Val)
    {	// insert value in priority order
        c.push_back(_Val);
        push_heap(c.begin(), c.end(), comp);
    }

    void pop()
    {	// erase highest-priority element
        pop_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }

protected:
    Container c;	// the underlying container
    Compare comp;	// the comparator functor

public:
    void swap(Myt& right)
        _NOEXCEPT_OP(_Is_nothrow_swappable<Container>::value
            && _Is_nothrow_swappable<Compare>::value)
    {	// exchange contents with right
        _Swap_adl(c, right.c);
        _Swap_adl(comp, right.comp);
    }
};

// PriorityQueue TEMPLATE FUNCTIONS
template<class _Ty,
    class Container,
    class Compare,
    class = enable_if_t<_Is_swappable<Container>::value && _Is_swappable<Compare>::value>> inline
    void swap(PriorityQueue<_Ty, Container, Compare>& _Left,
        PriorityQueue<_Ty, Container, Compare>& right)
    _NOEXCEPT_OP(_NOEXCEPT_OP(_Left.swap(right)))
{	// swap _Left and right queues
    _Left.swap(right);
}


//template<class _Ty,
//    class Container,
//    class Compare,
//    class Alloc>
//    struct usesAllocator<PriorityQueue<_Ty, Container, Compare>, Alloc>
//    : std::usesAllocator<Container, Alloc>
//{	// true_type if container allocator enabled
//};
