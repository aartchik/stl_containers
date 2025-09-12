#include <iostream>
#include "priority_queue.hpp"
#


int main()
{
    priority_queue<int> arr;
    arr.push(5);
    arr.push(10);
    arr.push(101);
    arr.push(2);
    arr.push(18);
    arr.push(-25);
    

    while (!arr.empty())
    {
        std::cout << arr.top() << " " << arr.size() << std::endl;
        arr.pop();
    }


}
