#ifndef VECTOR_H_
#define VECTOR_H_
#define LAB_VECTOR_EXCEPTIONS 2

#include <cstddef>
#include <algorithm>
#include <type_traits>
#include "allocator.hpp"

namespace containers {



    template <typename T, typename Allocator = std::allocator<T>>
    class vector
    {
    public:
        using value_type = T;
        using allocator_type = Allocator; 
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;


    private:
        size_type capacity_;
        size_type size_;
        Allocator alloc; 
        pointer array_;

    template <bool IsConst>
    class base_iterator
    {
        friend class vector<T, Allocator>;
        using pointer_type = typename std::conditional<IsConst, const T*, T*>::type;
        using reference_type = typename std::conditional<IsConst, const T&, T&>::type;
        
        base_iterator(const_pointer  ptr);

    public:
        reference_type operator*() const;
        pointer_type operator->() const;

        base_iterator& operator++();
        base_iterator operator++(int);

        base_iterator& operator--();
        base_iterator operator--(int);

        bool operator==(const base_iterator& other) const;
        bool operator!=(const base_iterator& other) const;

    private:
        operator base_iterator<true>() const { return base_iterator<true>(value); }
        T* value;
    };

    using iterator = base_iterator<false>;
    using const_iterator = base_iterator<true>;
    //using reverse_iterator = 
    //using const_reverse_iterator =     


    public:
        vector();
        vector(size_type n);
        vector(size_type n, const_reference value);
        //vector(const vector &other);
        //vector &operator=(vector other);
        ~vector();

        //vector& operator=(const vector& other);
        //vector& operator=(vector&& other);
        //vector& operator=(std::initializer_list<value_type> ilist);
        

    //Element access
        reference operator[](size_type index);
        const_reference operator[](size_type index) const;

        reference at(size_type index);
        const_reference at(size_type index) const;

        reference front();
        const_reference front() const;

        reference back();
        const_reference back() const;

    //Iterators
        iterator begin() noexcept;
        iterator end()  noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        iterator rbegin() noexcept;
        iterator rend()  noexcept;
        const_iterator crbegin() const noexcept;
        const_iterator crend() const noexcept;

    //capacity
        bool empty() const;
        size_type size() const;
        void reserve(size_type newcap);
        size_type capacity() const;
        void shrink_to_fit();

    //modifiers    
        void clear();

        void push_back(const_reference value);
        void push_back(T&& value);

        template <typename... Args>
        void emplace_back(Args&&... args);
        template <typename... Args>
        reference emplace_back(Args&&... args);

        void pop_back();


        void resize(size_type n);
        void resize(size_type n, const_reference value);

};

}
#include "vector_impl.hpp"
#include "allocator.hpp"

#endif  // vector_H


