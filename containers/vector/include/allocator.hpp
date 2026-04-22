#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cstddef>

template <typename T>
struct allocator
{

    using value_type = T;
    using pointer = value_type*;

    pointer allocate(size_t count)
    {
//        return reinterpret_cast<T*>(new char[sizeof(T) * count]);
        return static_cast<pointer>(operator new(sizeof(T) * count));
    }
    
    void deallocate(pointer ptr, size_t)
    {
    //    delete[] reinterpret_cast<char*>(ptr);
        operator delete(ptr);
    }

    template <typename U, typename... Args>
    void construct(U* ptr, const Args&... args)
    {
        new (ptr) U(args...);
    }
    
    template <typename U>
    void destroy(U* ptr)
    {
        ptr->~U();
    }

    template <typename U>
    allocator(allocator<U>) {}

    allocator() = default;

    template <typename U>
    struct rebind
    {
        using other = allocator<U>;
    };
};

#endif
