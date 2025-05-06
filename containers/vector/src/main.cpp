#include <iostream>
#include "vector.hpp"
using namespace containers;

int main()
{
    vector<int, allocator<int>> arr1(7);
    vector<std::string, allocator<std::string>> arr2(20);
    const vector<double, allocator<double>> arr3(25);

    int x = 25;
    std::string y = "test";

    arr1[5];
    arr2[5];
    arr3[10];

    arr1.at(5);
    arr2.at(5);
    arr3.at(5);


    arr1.front();
    arr2.front();
    arr3.front();

    arr1.back();
    arr2.back();
    arr3.back();

    arr1.begin();
    arr2.begin();
    arr3.cbegin();

    arr1.end();
    arr2.end();
    arr3.cend();

    arr1.empty();
    arr2.empty();
    arr3.empty();

    arr1.size();
    arr2.size();
    arr3.size();

    arr1.reserve(10000);
    arr2.reserve(10000);

    arr1.capacity();
    arr2.capacity();
    arr3.capacity();

    arr1.shrink_to_fit();
    arr2.shrink_to_fit();

    arr1.clear();
    arr2.clear();

    arr1.push_back(x);
    arr2.push_back(y);
    //arr1.push_back(25);
    //arr2.push_back("T&&");

    arr1.pop_back();
    arr2.pop_back();

    arr1.resize(100);
    arr2.resize(25, "resize");

    vector <std::string, allocator<std::string>> test(5);
    int i = 0;

    for (auto it = test.begin(); it != test.end(); ++it, ++i)
    {
        std::cout << i << " " << *it << std::endl;
    }
    std::cout << std::endl;

    /*for (auto it = --test.end(); it != --test.begin(); --it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;*/

    


}