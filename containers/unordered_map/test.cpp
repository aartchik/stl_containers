#include <unordered_map>
#include <list>
#include <iostream>


struct A {
	int a;
};

int main() {
	std::list<int> list;
	list.push_back(10);
	auto x = list.begin();
	x;
	std::cout << *x;
}
