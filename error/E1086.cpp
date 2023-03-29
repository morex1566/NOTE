/*
	E1086	: 개체에 멤버 함수 "MYCLASS::returnData"과(와) 호환되지 않는 형식 한정자가 있습니다.
	해결	: function뒤에 const를 붙입니다.
	의미	: function뒤에 const는 함수가 호출된 개체를 수정하지 않는 '읽기 전용'을 의미합니다.
*/

#include <iostream>

class MYCLASS
{
public:
	// E1086 error solved!
	const int& returnData() const { return data; }

private:
	int data = 4;
};

int main()
{
	MYCLASS classs = MYCLASS();
	const MYCLASS& classing = classs;

	// E1086 error triggered!
	classing.returnData();
}