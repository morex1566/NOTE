/*
	C2027	: 정의되지 않은 형식을 사용했습니다.
	해결	: 몇몇 상황에서는 forward-declare 말고, 올바른 header를 #include 합니다.
	의미	: std::shared_ptr과 같은 wrapping class는 header정보를 선언부분부터 알려줘야 합니다.
*/

#include <iostream>
#include <memory>

// C2102 error caution!
class TEST;

// C2102 error solved!
class TEST
{
public:
private:
};

int main()
{
	// C2102 error triggered!
	std::unique_ptr<TEST> sp;
}