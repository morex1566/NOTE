/*
	noexcept c++11      : 예외가 생기지 않는다는 것을 명시할 수 있습니다.
    feature             : 1. 컴파일러는 이 키워드를 통해 코드를 좀 더? 최적화를 진행할 수 있습니다.
                          2. 의미적으로 코드의 가독성을 높입니다.
    reference           : https://stackoverflow.com/questions/10787766/when-should-i-really-use-noexcept
    when i use it       : 1. 이동 작업(할당 연산자 이동 및 생성자 이동)
                          2. 스왑 작업
                          3. 메모리 할당 해제자(operator delete, operator delete[])
                          4. 소멸자(noexcept(true)만들지 않는 한 암시적으로 존재하지만 noexcept(false))
*/

#include <iostream>
#include <vector>
using namespace std;
class A{
 public:
    A(int){cout << "A(int)" << endl;}
    A(const A&){cout << "A(const A&)" << endl;}
    A(const A&&) noexcept {cout << "A(const A&&)" << endl;}
    ~A(){cout << "~S()" << endl;}
};

int main() {
    vector<A> a;
    cout << a.capacity() << endl;
    a.emplace_back(1);
    cout << a.capacity() << endl;
    a.emplace_back(2);
    cout << a.capacity() << endl;
    return 0;
}