#ifndef vector_IMPL_H_
#define vector_IMPL_H_

#include <math.h>
#include "vector.hpp"

size_t next_power_of_two(size_t n)
{
    if (n == 0)
        return 1;
    return static_cast<size_t>(std::pow(2, std::ceil(std::log2(n))));
}

namespace containers {

    template <typename T>
    template <bool IsConst>
    typename  vector<T>::base_iterator<IsConst>::base_iterator(typename vector<T>::const_pointer  ptr): value(const_cast<T*>(ptr)) {}

    template <typename T>
    template <bool IsConst>
    typename vector<T>::template typename base_iterator<IsConst>::reference_ttemplate ype vector<T>::base_iterator<IsConst>::operator*() const
    {
        return *value;
    }

    template <typename T>
    template <bool IsConst>
    vector<T>::template base_iterator<IsConst>::pointer_type vector<T>::base_iterator<IsConst>::operator->() const
    {
        return value;
    }

    template <typename T>
    template <bool IsConst>
    vector<T>::template base_iterator<IsConst>& vector<T>::base_iterator<IsConst>::operator++() 
    {
        return ++value;
    }

    template <typename T>
    template <bool IsConst>
    vector<T>::template base_iterator<IsConst> vector<T>::base_iterator<IsConst>::operator++(int)
    {
        base_iterator copy = *this;
        ++(value);
        return copy;
    }

    template <typename T>
    template <bool IsConst>
    vector<T>::template base_iterator<IsConst>& vector<T>::base_iterator<IsConst>::operator--()
    {
        return --value;
    }

    template <typename T>
    template <bool IsConst>
    vector<T>::template base_iterator<IsConst> vector<T>::base_iterator<IsConst>::operator--(int)
    {
        base_iterator copy = *this;
        --(value);
        return copy;
    }

    template <typename T>
    template <bool IsConst>
    bool vector<T>::base_iterator<IsConst>::operator==(const vector<T>::base_iterator<IsConst>& other) const
    {
        return this == &other;
    }

    template <typename T>
    template <bool IsConst>
    bool vector<T>::base_iterator<IsConst>::operator!=(const vector<T>::base_iterator<IsConst>& other) const
    {
        return !(this == &other);
    }

    

    template <typename T>
    typename vector<T>::vector(size_type n): capacity_(next_power_of_two(n)), size_(n), array_(reinterpret_cast<T*>(new char[sizeof(T) * size_]))
    {
        size_t index = 0;
        try
        {
            for (; index < size_; index++)
            {
                new (array_ + index) T();
            }
        }
        catch (std::exception&)
        {
            for (size_t oldindex = 0; oldindex < index; oldindex++)
            {
                (array_ + oldindex)->~T();
            }
            delete[] reinterpret_cast<char *>(array_);
            throw;
        }
    }
    
    template <typename T>
    typename vector<T>::vector(const vector& other) : capacity_(other.capacity_), size_(other.size_), array_(reinterpret_cast<T*>(new char[sizeof(T) * size_]))
    {
        size_t index = 0;
        try
        {
            for (; index < size_; index++)
            {
                new (array_ + index) T(other.array_[index]);
            }
        }
        catch (std::exception&)
        {
            for (size_t oldindex = 0; oldindex < index; oldindex++)
            {
                (array_ + oldindex)->~T();
            }
            delete[] reinterpret_cast<char *>(array_);
            throw;
        }
    }



    template <typename T>
    vector<T>& vector<T>::operator=(vector<T> other)
    {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(array_, other.array_);
        return *this;
    }

    template <typename T>
    size_type vector<T>::size() const
    {
        return size_;
    }

    template <typename T>
    vector<T>::~vector()
    {
        for (size_t index = 0; index < size_; index++)
        {
            (array_ + index)->~T();
        }
        delete[] reinterpret_cast<char *>(array_);
    }

    template <typename T>
    size_type vector<T>::capacity() const 
    {
        return capacity_;
    }

    template <typename T>
    bool vector<T>::empty() const 
    {
        return size_ == 0;
    }

    template <typename T>
    void vector<T>::resize(size_type n)
    {
        if (n==size_)
        {
            return;
        }
        else if (n>size_)
        {
            if (n > capacity_)
            {
                reserve(next_power_of_two(n));
            }
            size_t index = size_;
            try
            {
                for (; index < n; index++)
                {
                    new (array_ + index) T();
                }
            }
            catch (std::exception&)
            {
                for (size_t oldindex = size_; oldindex < index; oldindex++)
                {
                    (array_ + oldindex)->~T();
                }
                throw;
            }
        }
        else if (n < size_)
        {
            for (size_t index = n; index < size_; index++)
            {
                (array_ + index)->~T();
            }
        }
        size_ = n;
    }


    template <typename T>
    void vector<T>::reserve(size_type newcap)
    {
        size_type newcap_pow = next_power_of_two(newcap);
        if (newcap <= capacity_)
        {
            return;
        }

//        T *newarr = reinterpret_cast<T *>(new char[sizeof(T) * newcap_pow]);
        T* newarr = alloc.allocate(sizeof(T) * newcap_pow);
        size_t index = 0;
        try
        {
            for (; index < size_; index++)
            {
                //new(newarr + index) T(array_[index]);
                alloc.construct(newarr + index, array_[index]);
            }
        }
        catch (std::exception&)
        {
            for (size_t oldindex = 0; oldindex < index; oldindex++)
            {
                //(newarr + oldindex)->~T();
                alloc.destroy(newarr + oldindex);
            }
            //delete[] reinterpret_cast<char*>(newarr);
            alloc.deallocate(newarr, sizeof(T) * capacity);
            throw;
        }
        for (size_t index = 0; index < size_; index++)
        {
            //(array_ + index)->~T();
            alloc.destroy(array_ + index);
        }
        //delete[] reinterpret_cast<char*>(array_);
        alloc.deallocate(array_, sizeof(T) * capacity);
        array_ = newarr;
        capacity_ = newcap_pow;
    }



    template <typename T>
    T& vector<T>::operator[](size_type index)
    {
        return array_[index];
    }

    template <typename T>
    const T& vector<T>::operator[](size_type index) const
    {
        return array_[index];
    }

    template <typename T>
    void vector<T>::push_back(const T& t)
    {
        if (size_ == capacity_)
        {
            reserve(size_ == 0 ? 1 : capacity_ * 2);
        }
        new(array_ + size_) T(t);
        ++size_;
    }

    template <typename T>
    void vector<T>::pop_back()
    {
        if (size_ == 0)
        {
            return;
        }
        (array_ + size_ - 1)->~T();
        --size_;
    }


    template <typename T>
    void vector<T>::shrink_to_fit()
    {
        if (size_ == capacity_)
        {
            return;
        }
        T *newarr = reinterpret_cast<T *>(new char[sizeof(T) * size_]);
        size_t index = 0;
        try
        {
            for (; index < size_; index++)
            {
                new (newarr + index) T(array_[index]);
            }
        }
        catch (std::exception&)
        {
            for (size_t oldindex = 0; oldindex < index; oldindex++)
            {
                (newarr + oldindex)->~T();
            }
            delete[] reinterpret_cast<char *>(newarr);
            throw;
        }
        for (size_t index = 0; index < size_; index++)
        {
            (array_ + index)->~T();
        }
        delete[] reinterpret_cast<char *>(array_);
        array_ = newarr;
        capacity_ = size_;
    }

    template <typename T>
    void vector<T>::clear()
    {
        for (size_t index = 0; index < size_; index++)
        {
            (array_ + index)->~T();
        }
        size_ = 0;
        
    }

}
#include "vector.hpp"

#endif // vector_H
