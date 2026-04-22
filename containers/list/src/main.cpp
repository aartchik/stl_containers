

#include <iostream>
#include "list.hpp"

template <typename T>
void print(const container::List<T>& arr)
{
    for (auto it = arr.cbegin(); it!=arr.cend(); ++it)
    {
        std::cout << *it << std::endl;
    }
}


int main()
{

    container::List<double> arr1(10);
    container::List<double> arr2(10, 2.5);
    const container::List<double> arr3(5);
    arr1.front();
    arr2.front();
    arr3.front();

    arr1.back();
    arr2.back();
    arr3.back();





    
    arr3.empty();
    arr3.size();

    *(++arr1.begin());
    *(arr3.cbegin());

    arr2.insert(arr2.begin(), 7.5);
    arr2.erase(arr2.begin());


    return 0;
}