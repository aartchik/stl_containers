
#include "list_impl.hpp"

#include <iostream>



int main()
{   
    container::List<int> arr(10, -7);
    std::cout << arr.size() << " ";
    int i = 1;
    for (auto it = arr.begin(); it != arr.end(); ++it, ++i)
    {
        std::cout << i << " " << *it << "    ";
    }
}