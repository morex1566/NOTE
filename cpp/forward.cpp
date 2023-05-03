/*
 *      about : std::forward
 *      what  : 특히 template에서 r-value 인지 l-value인지 추론하기 어려운 경우에 사용한다.
 */

#include <iostream>	
#include <utility>

using namespace std;

struct myStruct
{};

void func(myStruct& s) { cout << "Pass by L-ref\n"; } 
void func(myStruct&& s) { cout << "Pass by R-ref\n"; }  // R-value Reference 오버로딩

template<typename T>   // 여러가지 타입을 T로 받을 수 있다.
void func_wrapper(T t)
{
    func(std::forward<T>(t));
}

int main()
{
	myStruct s;

	func_wrapper(s); // compiler 해석에 따른 R-value Reference 오버로딩
	func_wrapper(myStruct());  // R-value Reference 오버로딩
}