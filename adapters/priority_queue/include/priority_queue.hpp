#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <vector>
#include <cstdio>



template <typename T>
class priority_queue
{
private:
    std::vector<T> array_;

public:
    //Element access
    const T& top() const;

    //Capacity
    bool empty() const;
    size_t size() const;
    
    //Modifiers
    void push(const T& value);
    void pop();

private:
    void siftUp(size_t n);
    void siftDown(size_t n);
     
};

#include "priority_queue_impl.hpp"



#endif
