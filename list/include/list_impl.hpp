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

        template <bool IsConst>
        class base_iterator
        {
        public:
            using pointer_type = typename std::conditional<IsConst, const T *, T *>::type;
            using reference_type = typename std::conditional<IsConst, const T &, T &>::type;

            base_iterator() : current(nullptr) {}
            base_iterator(Node *ptr) : current(ptr) {}
            base_iterator(const base_iterator &other) : current(other.current) {}
            base_iterator &operator=(const base_iterator &) = default;

            reference_type operator*() const { return current->data_; }
            pointer_type operator->() const { return &current->data_; }
            base_iterator &operator++()
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
            base_iterator &operator--()
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

            bool operator==(const base_iterator &other) const { return (current == other.current); }
            bool operator!=(const base_iterator &other) const { return !(*this == other); }

        private:
            Node *current;
        };

    public:
        using iterator = base_iterator<false>;
        using const_iterator = base_iterator<true>;
        //using reverse_iterator = std::reverse_iterator<iterator>;
        //using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        List(size_t count);
        List(size_t count, const T& value);

        template <class InputIt>
        List(InputIt first, InputIt last);

        List(const List &other);
        List &operator=(List other);
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
            Node* new_node = Node(nullptr, value);
            if (pos == begin())
            {
                new_node->next = head;
                if (head)
                    head->prev = new_node;
                head = new_node;
            }
            else if (pos == end())
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
}


#endif 