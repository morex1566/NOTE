
#include "header.h"
#include <iostream>

int extern_value = 5;
int static_value = 10; // C2086 : ������ ����

int main()
{
    std::cout << extern_value;
    std::cout << static_value;
}