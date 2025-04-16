#ifndef LIST_IMPL_HPP_
#define LIST_IMPL_HPP_

#include "list.hpp"

namespace container
{


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
                tail = new_node;
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