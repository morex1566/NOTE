/*
	C2665	: 모든 인수 형식을 변환할 수 있는 오버로드된 함수가 없습니다.
	해결	: std::make_shared<!type!>(!constructor argument!)
	의미	: 올바른 smart pointer 생성 방법을 사용합니다.
*/

#include <iostream>
#include <memory>

class TEST
{
public:
	TEST(int data) : value(data) {}

private:
	int value;
};

int main()
{
	// C2665 error triggered!
	std::unique_ptr<TEST> sp = std::make_unique<TEST>(new TEST(4));

	// C2665 error solved!
	std::unique_ptr<TEST> sp_solved = std::make_unique<TEST>(4);
	// or
	std::unique_ptr<TEST> sp_solved2(new TEST(4));
}