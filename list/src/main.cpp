
#include "list_impl.hpp"

#include <iostream>



int main()
{
    container::List<std::string> arr(3, "string");
    arr.insert(++arr.begin(), "a");
    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        std::cout << *it << " ";
    }
}