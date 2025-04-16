
#include "list_impl.hpp"

#include <iostream>



int main()
{
    container::List<std::string> arr(0);
    arr.insert(arr.end(), "a");


    return 0;  
}