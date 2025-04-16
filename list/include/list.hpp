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

    private:
        class Node
        {
        public:
            Node* prev;
            value_type data_;
            Node* next;
            Node(Node* prev, const_reference value);
            Node(const Node& other);
            Node& operator=(Node other);
            Node* operator->();
            Node& operator*();
        };

        size_t size_;
        Node* head;
        Node* tail;

        template <bool IsConst>
        class base_iterator
        {
            using pointer_type = typename std::conditional<IsConst, const T*, T*>::type;
            using reference_type = typename std::conditional<IsConst, const T&, T&>::type;
        public:

            base_iterator() : current(nullptr) {}
            base_iterator(Node* ptr) : current(ptr) {}
            base_iterator(const base_iterator& other) : current(other.current) {}
            reference_type operator*() const { return current->data_; }
            pointer_type operator->() const { return &current->data_; }
            base_iterator& operator++()
            {
                current = current->next;
                return *this;
            }
            base_iterator operator++(int)
            {
                base_iterator copy = *this;
                ++(*this);
                return copy;
            }
            base_iterator& operator--()
            {
                current = current->prev;
                return *this;
            }
            base_iterator operator--(int)
            {
                base_iterator copy = *this;
                --(*this);
                return copy;
            }

            bool operator==(const base_iterator& other) const { return (current == other.current); }
            bool operator!=(const base_iterator& other) const { return !(*this == other); }

            operator base_iterator<true>() const {return base_iterator<true>(current);}
            operator Node*() const { return current;}

        private:
            Node* current;
        };

    public:


        using iterator = base_iterator<false>;
        using const_iterator = base_iterator<true>;
        //using reverse_iterator = std::reverse_iterator<iterator>;
        //using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        List(size_t count);
        List(size_t count, const_reference value);

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
        iterator begin() noexcept;
        iterator end() noexcept;
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

#endif 