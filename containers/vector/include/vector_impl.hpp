#ifndef vector_IMPL_H_
#define vector_IMPL_H_

#include <math.h>
#include "vector.hpp"
#include "allocator.hpp"
#include <exception>


size_t next_power_of_two(size_t n)
{
    if (n == 0)
        return 1;
    return static_cast<size_t>(std::pow(2, std::ceil(std::log2(n))));
}

namespace containers {

    template <typename T, typename Allocator>
    template <bool IsConst>
    vector<T, Allocator>::base_iterator<IsConst>::base_iterator(typename vector<T, Allocator>::const_pointer  ptr): value(const_cast<T*>(ptr)) {}

    template <typename T, typename Allocator>
    template <bool IsConst>
    typename vector<T, Allocator>::base_iterator<IsConst>::reference_type vector<T, Allocator>::base_iterator<IsConst>::operator*() const
    {
        return *value;
    }

    template <typename T,  typename Allocator>
    template <bool IsConst>
    typename vector<T, Allocator>::base_iterator<IsConst>::pointer_type vector<T, Allocator>::base_iterator<IsConst>::operator->() const
    {
        return value;
    }

    template <typename T,  typename Allocator>
    template <bool IsConst>
    vector<T, Allocator>::base_iterator<IsConst>& vector<T, Allocator>::base_iterator<IsConst>::operator++() 
    {
        ++value;
        return *this;
    }

    template <typename T,  typename Allocator>
    template <bool IsConst>
    vector<T, Allocator>::template base_iterator<IsConst> vector<T, Allocator>::base_iterator<IsConst>::operator++(int)
    {
        base_iterator copy = *this;
        ++(value);
        return copy;
    }

    template <typename T,  typename Allocator>
    template <bool IsConst>
    vector<T, Allocator>::template base_iterator<IsConst>& vector<T, Allocator>::base_iterator<IsConst>::operator--()
    {
        --value;
        return *this;
    }

    template <typename T,  typename Allocator>
    template <bool IsConst>
    vector<T, Allocator>::template base_iterator<IsConst> vector<T, Allocator>::base_iterator<IsConst>::operator--(int)
    {
        base_iterator copy = *this;
        --(value);
        return copy;
    }

    template <typename T,  typename Allocator>
    template <bool IsConst>
    bool vector<T, Allocator>::base_iterator<IsConst>::operator==(const vector<T, Allocator>::base_iterator<IsConst>& other) const
    {
        return (value == other.value);
    }

    template <typename T,  typename Allocator>
    template <bool IsConst>
    bool vector<T, Allocator>::base_iterator<IsConst>::operator!=(const vector<T, Allocator>::base_iterator<IsConst>& other) const
    {
        return !(value == other.value);
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() noexcept
    {
        return base_iterator<false>(array_);
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::end() noexcept
    {
        return base_iterator<false>(array_ + size_);
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cbegin() const noexcept
    {
        return base_iterator<true>(array_);
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cend() const noexcept
    {
        return base_iterator<true>(array_ + size_);
    }


    template <typename T, typename Allocator>
    vector<T, Allocator>::vector(): capacity_(2), size_(0), alloc(), array_(alloc.allocate(sizeof(T) * capacity_)) {}
    

    template <typename T,  typename Allocator>
    vector<T, Allocator>::vector(size_type n) : capacity_(next_power_of_two(n)), size_(n), alloc(), array_(alloc.allocate(sizeof(T) * capacity_))
    {

        size_t index = 0;
        try
        {
            for (; index < size_; index++)
            {
                alloc.construct(array_ + index);
            }
        }
        catch (std::exception&)
        {
            for (size_t oldindex = 0; oldindex < index; oldindex++)
            {
                alloc.destroy(array_ + oldindex);
            }
            alloc.deallocate(array_, sizeof(T) * capacity_);
            throw;
        }
    }

    template <typename T, typename Allocator>
    vector<T, Allocator>::vector(size_type n, const_reference value) : capacity_(next_power_of_two(n)), size_(n), alloc(), array_(alloc.allocate(sizeof(T)* capacity_))
    {

        size_t index = 0;
        try
        {
            for (; index < size_; index++)
            {
                alloc.construct(array_ + index, value);
            }
        }
        catch (std::exception&)
        {
            for (size_t oldindex = 0; oldindex < index; oldindex++)
            {
                alloc.destroy(array_ + oldindex);
            }
            alloc.deallocate(array_, sizeof(T) * capacity_);
            throw;
        }
    }
    
 /*   template <typename T,  typename Allocator>
    typename vector<T, Allocator>::vector(const vector& other) : capacity_(other.capacity_), size_(other.size_), array_(reinterpret_cast<T*>(new char[sizeof(T) * size_]))
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
    }*/





    template <typename T, typename Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const
    {
        return size_;
    }

    template <typename T, typename Allocator>
    vector<T, Allocator>::~vector()
    {
        for (size_t index = 0; index < size_; index++)
        {
            alloc.destroy(array_ + index);
        }
        alloc.deallocate(array_, sizeof(T) * capacity_);
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const 
    {
        return capacity_;
    }

    template <typename T, typename Allocator>
    bool vector<T, Allocator>::empty() const 
    {
        return size_ == 0;
    }

    template <typename T, typename Allocator>
    void vector<T, Allocator>::resize(size_type n)
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
                    alloc.construct(array_ + index);
                }
            }
            catch (std::exception&)
            {
                for (size_t oldindex = size_; oldindex < index; oldindex++)
                {
                    alloc.destroy(array_ + oldindex);
                }
                throw;
            }
        }
        else if (n < size_)
        {
            for (size_t index = n; index < size_; index++)
            {
                alloc.destroy(array_ + index);
            }
        }
        size_ = n;
    }

    template <typename T, typename Allocator>
    void vector<T, Allocator>::resize(size_type n, const_reference value)
    {
        if (n == size_)
        {
            return;
        }
        else if (n > size_)
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
                    alloc.construct(array_ + index, value);
                }
            }
            catch (std::exception&)
            {
                for (size_t oldindex = size_; oldindex < index; oldindex++)
                {
                    alloc.destroy(array_ + oldindex);
                }
                throw;
            }
        }
        else if (n < size_)
        {
            for (size_t index = n; index < size_; index++)
            {
                alloc.destroy(array_ + index);
            }
        }
        size_ = n;
    }


    template <typename T, typename Allocator>
    void vector<T, Allocator>::reserve(size_type newcap)
    {
        size_type newcap_pow = next_power_of_two(newcap);
        if (newcap_pow <= capacity_)
        {
            return;
        }

//        T *newarr = reinterpret_cast<T *>(new char[sizeof(T) * newcap_pow_pow]);
        pointer newarr = alloc.allocate(sizeof(T) * newcap_pow);
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
            alloc.deallocate(newarr, sizeof(T) * capacity_);

            throw;
        }
        for (size_t index = 0; index < size_; index++)
        {
            //(array_ + index)->~T();
            alloc.destroy(array_ + index);
        }
        //delete[] reinterpret_cast<char*>(array_);
        alloc.deallocate(array_, sizeof(T) * capacity_);
        array_ = newarr;
        capacity_ = newcap_pow;
    }


    template <typename T, typename Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("");
        return array_[index];
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::const_reference  vector<T, Allocator>::at(size_type index) const
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("");
        return array_[index];
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type index)
    {
        return array_[index];
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::const_reference  vector<T, Allocator>::operator[](size_type index) const
    {
        return array_[index];
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::reference  vector<T, Allocator>::front()
    {
        return *array_;
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::const_reference  vector<T, Allocator>::front() const
    {
        return *array_;
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::reference  vector<T, Allocator>::back()
    {
        return *(array_ + size_ - 1);
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::const_reference  vector<T, Allocator>::back() const
    {
        return *(array_ + size_ - 1);
    }




    template <typename T, typename Allocator>
    void vector<T, Allocator>::push_back(const_reference value)
    {
        if (size_ == capacity_)
        {
            reserve(size_ == 0 ? 1 : capacity_ * 2);
        }
        alloc.construct(array_ + size_, value);
        ++size_;
    }

    template <typename T, typename Allocator>
    void vector<T, Allocator>::pop_back()
    {
        if (size_ == 0)
        {
            return;
        }
        alloc.destroy(array_ + size_ - 1);
        --size_;
    }


    template <typename T, typename Allocator>
    void vector<T, Allocator>::shrink_to_fit()
    {
        if (size_ == capacity_)
        {
            return;
        }
        pointer newarr = alloc.allocate(sizeof(T) * size_);
        size_t index = 0;
        try
        {
            for (; index < size_; index++)
            {
                alloc.construct(newarr + index, array_[index]);
            }
        }
        catch (std::exception&)
        {
            for (size_t oldindex = 0; oldindex < index; oldindex++)
            {
                alloc.destroy(newarr + oldindex);
            }
            alloc.deallocate(newarr, sizeof(T) * size_);
            throw;
        }
        for (size_t index = 0; index < size_; index++)
        {
            (array_ + index)->~T();
        }
        alloc.deallocate(array_, sizeof(T) * size_);
        array_ = newarr;
        capacity_ = size_;
    }

    template <typename T, typename Allocator>
    void vector<T, Allocator>::clear()
    {
        for (size_t index = 0; index < size_; index++)
        {
            alloc.destroy(array_ + index);
        }
        size_ = 0;
        
    }

}
#include "vector.hpp"

#endif // vector_H
