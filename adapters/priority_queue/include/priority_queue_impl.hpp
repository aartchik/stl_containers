#ifndef PRIORITY_QUEUE_IMPL_HPP
#define PRIORITY_QUEUE_IMPL_HPP

#include "priority_queue.hpp"

template <typename T>
bool priority_queue<T>::empty() const
{
    return array_.empty();
}

template <typename T>
size_t priority_queue<T>::size() const
{
    return array_.size();
}


template <typename T>
void priority_queue<T>::push(const T& value)
{
    array_.push_back(value);
    siftUp(array_.size() - 1);
}


template <typename T>
void priority_queue<T>::siftUp(size_t n)
{
    if (n>0 && array_[(n-1)/2] > array_[n])
    {
        std::swap(array_[(n-1)/2], array_[n]);
        siftUp((n - 1) / 2);
    }
}

template <typename T>
const T& priority_queue<T>::top() const
{
    return array_[0];
}


template <typename T>
void priority_queue<T>::pop()
{
    std::swap(array_[0], array_[array_.size() - 1]);
    array_.pop_back();
    siftDown(0);
    
}

template <typename T>
void priority_queue<T>::siftDown(size_t n)
{
    if (array_[n*2 + 1] <= array_[n] || array_[n*2+2] <= array_[n])
    {
        if (array_[n * 2 + 1] <= array_[n * 2 + 2])
        {
            std::swap(array_[n], array_[n*2 + 1]);
        }
        else
        {
            std::swap(array_[n], array_[n * 2 + 2]);
        }
        siftDown(array_[n*2 + 1] <= array_[n*2 + 2] ? (n*2 + 1) : (n*2 + 2));
    }
} 
#endif
