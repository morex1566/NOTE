// Online C++ compiler to run C++ program online
#include <iostream>
#include <typeinfo>
#include <string>
#include <memory>

int main() {

	std::unique_ptr<int> datauptr = std::make_unique<int>(1);

	int* dataptr = datauptr.get();

	*dataptr = 2;

    return 0;
}