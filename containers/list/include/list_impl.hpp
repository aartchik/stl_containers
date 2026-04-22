#ifndef LIST_IMPL_HPP_
#define LIST_IMPL_HPP_

#include "list.hpp"

namespace container
{

    template <typename T>
    List<T>::base_Node::base_Node(base_Node* prev, base_Node* next): prev(prev), next(next) {}

    template <typename T>
    List<T>::base_Node::base_Node(): prev(this), next(this) {}


    template <typename T>
    List<T>::Node::Node(const_reference value): base_Node(), data_(value) {}

    template <typename T>
    List<T>::Node::Node(const Node& other): base_Node(other.prev, other.next), data_(other.data_) {}

    template <typename T>
    typename List<T>::Node& List<T>::Node::operator=(Node other)
    {
        std::swap(this->prev, other.prev);
        std::swap(data_, other.data_);
        std::swap(this->next, other.next);
        return *this;
    }



    template <typename T>
    List<T>::List(): size_(0), fakeNode(&fakeNode, &fakeNode) {}

    template <typename T>
    List<T>::List(size_t count): size_(count), fakeNode(&fakeNode, &fakeNode)
    {
        if (count == 0)
            return;
        
        Node* teil = new Node(value_type());
        teil->prev = &fakeNode;
        fakeNode.next = teil;
        for (size_t index = 1; index < count; index++)
        {
            teil->next = new Node(value_type());
            teil->next->prev = teil;
            teil = static_cast<Node*>(teil->next);
        }
        teil->next = &fakeNode;
        fakeNode.prev = teil;
    }


    template <typename T>
    List<T>::List(size_t count, const_reference value) : size_(count), fakeNode(&fakeNode, &fakeNode)
    {
        if (count == 0)
            return;
        
        Node* teil = new Node(value);
        teil->prev = &fakeNode;
        fakeNode.next = teil;
        for (size_t index = 1; index < count; index++)
        {
            teil->next = new Node(value);
            teil->next->prev = teil;
            teil = static_cast<Node*>(teil->next);
        }
        teil->next = &fakeNode;
        fakeNode.prev = teil;

    }

    template <typename T>
    List<T>::~List()
    {

        base_Node* teil = fakeNode.next;
        while (teil != &fakeNode)
        {
            base_Node* temp = teil;
            teil = teil->next;
            delete static_cast<Node*>(temp);
        }
    }

    template <typename T>
    template <bool IsConst>
    List<T>::base_iterator<IsConst>::base_iterator(const List<T>::base_Node* ptr): current(const_cast<base_Node*>(ptr)) {}



    template <typename T>
    template <bool IsConst>
    typename List<T>::template base_iterator<IsConst>::reference_type List<T>::base_iterator<IsConst>::operator*() const
    {
        return static_cast<Node*>(current)->data_;
    }

    template <typename T>
    template <bool IsConst>
    typename List<T>::template base_iterator<IsConst>::pointer_type List<T>::base_iterator<IsConst>::operator->() const
    {
        return &operator*();
    }
    
    template <typename T>
    template <bool IsConst>
    typename List<T>::template base_iterator<IsConst>& List<T>::base_iterator<IsConst>::operator++()
    {
        current = current->next;
        return *this;
    }

    template <typename T>
    template <bool IsConst>
    typename List<T>::template base_iterator<IsConst> List<T>::base_iterator<IsConst>::operator++(int)
    {
        base_iterator copy = *this;
        ++(*this);
        return copy;
    }

    template <typename T>
    template <bool IsConst>
    typename List<T>::template base_iterator<IsConst>& List<T>::base_iterator<IsConst>::operator--()
    {
        current = current->prev;
        return *this;
    }

    template <typename T>
    template <bool IsConst>
    typename List<T>::template base_iterator<IsConst> List<T>::base_iterator<IsConst>::operator--(int)
    {
        base_iterator copy = *this;
        --(*this);
        return copy;
    }

    template <typename T>
    template <bool IsConst>
    bool List<T>::base_iterator<IsConst>::base_iterator::operator==(const List<T>::base_iterator<IsConst>& other) const
    {
        return (current == other.current);
    }

    template <typename T>
    template <bool IsConst>
    bool List<T>::base_iterator<IsConst>::base_iterator::operator!=(const List<T>::base_iterator<IsConst>& other) const
    {
        return !(*this == other);
    }





    template <typename T>
    typename List<T>::iterator List<T>::begin() const noexcept
    {
        return iterator(fakeNode.next);
    }

    template <typename T>
    typename List<T>::iterator List<T>::end() const noexcept
    {
        return iterator(&fakeNode);
    }

    template <typename T>
    typename List<T>::const_iterator List<T>::cbegin() const noexcept
    {
        return const_iterator(fakeNode.next);
    }

    template <typename T>
    typename List<T>::const_iterator List<T>::cend() const noexcept
    {
        return const_iterator(&fakeNode);
    }
    
    template <typename T>
    typename List<T>::reference List<T>::front()
    {
        return *begin();
    }
    template <typename T>
    typename List<T>::reference List<T>::back()
    {
        return *(--end());
    }
    template <typename T>
    typename List<T>::const_reference List<T>::front() const
    {
        return *begin();

    }
    template <typename T>
    typename List<T>::const_reference List<T>::back() const
    {
        return *(--end());
    }

    // Capacity
    template <typename T>
    bool List<T>::empty() const noexcept  { return size_ == 0; }
    template <typename T>
    size_t List<T>::size() const noexcept {return size_;}

    //Modifers
    template <typename T>
    void List<T>::clear() noexcept
    {
        base_Node* head = fakeNode.next;
        while (head != &fakeNode)
        {
            base_Node* temp = head;
            head = head->next;
            delete static_cast<Node*>(temp);
        }
        fakeNode.prev = fakeNode.next = &fakeNode;
        size_ = 0;
    }

    template <typename T>
    typename List<T>::iterator List<T>::insert(const_iterator pos, const_reference value)
    {
        ++size_;
        Node* node = new Node(value);
        node->next = pos.current;
        node->prev = pos.current->prev;
        node->prev->next = node;
        pos.current->prev = node;
        return iterator(static_cast<base_Node*>(node));
    }


    template <typename T>
    typename List<T>::iterator List<T>::erase(const_iterator pos)
    {
        --size_;
        base_Node* node = pos.current;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        iterator ret(static_cast<base_Node*>(node->next));
        delete static_cast<Node*>(node);
        return ret;
        
    }
}


#endif 