#ifndef LIST_IMPL_HPP_
#define LIST_IMPL_HPP_

#include <exception>
#include <cstddef>

namespace container
{

    template <typename T>
    class List
    {

    public:
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using size_type = size_t;

    private:
        class Node
        {
        public:
            Node *prev;
            value_type data_;
            Node *next;
            Node(Node *prev, const_reference value);
            Node(const Node &other);
            Node &operator=(Node other);
            Node *operator->();
            Node &operator*();
        };

        size_t size_;
        Node *head;
        Node *tail;

        class iterator
        {
        public:
            using pointer_type = T*;
            using reference_type = T&;

            iterator() : current(nullptr) {}
            iterator(Node *ptr) : current(ptr) {}
            iterator(const iterator &other) : current(other.current) {}
            iterator(const const_iterator &other) : current(other.current) {}

            operator Node *() const { return current; }

            reference_type operator*() const { return current->data_; }
            pointer_type operator->() const { return &current->data_; }
            iterator &operator++()
            {
                current = current->next;
                return *this;
            }
            iterator operator++(int)
            {
                iterator copy = *this;
                ++(*this);
                return copy;
            }
            iterator &operator--()
            {
                current = current->prev;
                return *this;
            }
            iterator operator--(int)
            {
                iterator copy = *this;
                --(*this);
                return copy;
            }

            bool operator==(const iterator &other) const { return (current == other.current); }
            bool operator!=(const iterator &other) const { return !(*this == other); }

            Node *current;
        private:
        };

        class const_iterator
        {
        public:
            using pointer_type = const T*;
            using reference_type = const T&;

            const_iterator() : current(nullptr) {}
            const_iterator(Node *ptr) : current(ptr) {}
            const_iterator(const iterator &other) : current(other.current) {}
            const_iterator(const const_iterator &other) : current(other.current) {}

            operator Node*() const { return current; }

            reference_type operator*() const { return current->data_; }
            pointer_type operator->() const { return &current->data_; }
            const_iterator &operator++()
            {
                current = current->next;
                return *this;
            }
            const_iterator operator++(int)
            {
                const_iterator copy = *this;
                ++(*this);
                return copy;
            }
            const_iterator &operator--()
            {
                current = current->prev;
                return *this;
            }
            const_iterator operator--(int)
            {
                const_iterator copy = *this;
                --(*this);
                return copy;
            }

            bool operator==(const const_iterator &other) const { return (current == other.current); }
            bool operator!=(const const_iterator &other) const { return !(*this == other); }

        private:
            Node *current;
        };

    public:

        //using reverse_iterator = std::reverse_iterator<iterator>;
        //using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        List(size_t count);
        List(size_t count, const_reference value);

        template <class InputIt>
        List(InputIt first, InputIt last);

        List(const List &other);
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
        iterator insert(const_iterator pos, size_type count, const T &value);
        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last);
    };

    template <typename T>
    List<T>::Node::Node(Node *prev, const_reference value): prev(prev), data_(value), next(nullptr) {}

    template <typename T>
    List<T>::Node::Node(const Node &other): prev(other.prev), data_(other), next(other.next) {}

    template <typename T>
    typename List<T>::Node& List<T>::Node::operator=(Node other)
    {
        std::swap(prev, other.prev);
        std::swap(data_, other.data_);
        std::swap(next, other.next);
        return *this;
    }

    template <typename T>
    typename List<T>::Node* List<T>::Node::operator->()
    {
        return this;
    }

    template <typename T>
    typename List<T>::Node& List<T>::Node::operator*()
    {
        return *this;
    }


    template <typename T>
    List<T>::List(size_t count): size_(count), head(nullptr), tail(nullptr)
    {
        if (count == 0)
            return;
        
        head = new Node(nullptr, value_type());
        tail = head;
        for (size_t index = 1; index < size_; index++)
        {
            tail->next = new Node(tail, value_type());
            tail = tail->next;
        }
    }


    template <typename T>
    List<T>::List(size_t count, const_reference value): size_(count), head(nullptr), tail(nullptr)
    {
        if (count == 0)
            return;
        
        head = new Node(nullptr, value);
        tail = head;

        for (size_t index = 1; index < size_; index++)
        {
            tail->next = new Node(tail, value);
            tail = tail->next;
        }
    }

    template <typename T>
    List<T>::~List()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    template <typename T>
    typename List<T>::iterator List<T>::begin() noexcept
    {
        return iterator(head);
    }

    template <typename T>
    typename List<T>::iterator List<T>::end() noexcept
    {
        return iterator(tail->next);
    }

    template <typename T>
    typename List<T>::const_iterator List<T>::cbegin() const noexcept
    {
        return const_iterator(head);
    }

    template <typename T>
    typename List<T>::const_iterator List<T>::cend() const noexcept
    {
        return const_iterator(tail->next);
    }
    
    template <typename T>
    typename List<T>::reference List<T>::front() { return head->data_; }
    template <typename T>
    typename List<T>::reference List<T>::back() { return tail->data_; }
    template <typename T>
    typename List<T>::const_reference List<T>::front() const { return head->data_; }
    template <typename T>
    typename List<T>::const_reference List<T>::back() const { return tail->data_; }

    // Capacity
    template <typename T>
    bool List<T>::empty() const noexcept  { return size_ == 0; }
    template <typename T>
    size_t List<T>::size() const noexcept {return size_;}

    //Modifers
    template <typename T>
    void List<T>::clear() noexcept
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size_ = 0;
    }

    template <typename T>
    typename List<T>::iterator List<T>::insert(const_iterator pos, const_reference value)
    {

       // try
        //{
            Node* new_node = new Node(nullptr, value);
            if (pos == cbegin())
            {
                new_node->next = head;
                if (head)
                    head->prev = new_node;
                head = new_node;
            }
            else if (pos == cend())
            {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node->next;
            }
            else
            {
                Node* current_node = pos;
                new_node->prev = current_node->prev;
                new_node->next = current_node;
                current_node->prev->next = new_node;
                current_node->prev = new_node;
            }
            size_++;

            return iterator(new_node);
        //}
        //catch (std::exception& )
        //{
        }

        template <typename T>
        typename List<T>::iterator List<T>::erase(const_iterator pos)
        {
            if (pos == cbegin())
            {
                head->next->prev = nullptr;
                
            }
        }
}


#endif 