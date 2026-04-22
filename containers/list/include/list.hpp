#ifndef LIST_HPP_
#define LIST_HPP_


#include <exception>
#include <cstddef>

namespace container
{

    template <typename T>
    class List
    {

        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using size_type = size_t;

    public:


        struct base_Node
        {
            friend class List;
            base_Node* prev;
            base_Node* next;
            base_Node();
            base_Node(base_Node* prev, base_Node* next);
            base_Node(const base_Node& other) = default;
        };

        struct Node: base_Node
        {
            friend class List<T>;
        public:
            value_type data_;
            explicit Node(const_reference value);
            Node(const Node& other);
            Node& operator=(Node other);

        };

        size_t size_;
        base_Node fakeNode;



        template <bool IsConst>
        class base_iterator
        {
            friend List<T>;
            using base_ptr = typename std::conditional<IsConst, const base_Node*, base_Node*>::type;
            using pointer_type = typename std::conditional<IsConst, const T*, T*>::type;
            using reference_type = typename std::conditional<IsConst, const T&, T&>::type;
        public:

            explicit base_iterator(const base_Node* ptr);
            
            reference_type operator*() const;
            pointer_type operator->() const;

            base_iterator& operator++();
            base_iterator operator++(int);

            base_iterator& operator--();
            base_iterator operator--(int);


            bool operator==(const base_iterator& other) const;
            bool operator!=(const base_iterator& other) const;

            operator base_iterator<true>() const { return base_iterator<true>(current); }
            //explicit operator Node*() const { return static_cast<Node*>(current);}

        private:
            base_Node* current;
        };

    public:


        using iterator = base_iterator<false>;
        using const_iterator = base_iterator<true>;
        //using reverse_iterator = std::reverse_iterator<iterator>;
        //using const_reverse_iterator = std::reverse_iterator<const_iterator>;


        List();
        explicit List(size_t count);
        explicit List(size_t count, const_reference value);

        template <class InputIt>
        List(InputIt first, InputIt last);

        List(const List& other);
        List& operator=(List other);
        ~List();

        // Element access

        reference front();
        reference back();
        const_reference front() const;
        const_reference back() const;

        // Iterators
        iterator begin() const noexcept;
        iterator end()  const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        // Capacity
        bool empty() const noexcept;
        size_t size() const noexcept;

        // Modifers
        void clear() noexcept;
        iterator insert(const_iterator pos, const_reference value);
        iterator insert(const_iterator pos, size_type count, const T& value);
        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last);
    };
}
#include "list_impl.hpp"
#endif 