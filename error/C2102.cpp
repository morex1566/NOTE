/*
	C2102	: '&'에는 l-value가 있어야 합니다.
	해결	: const reference type에서 const를 제거합니다.
	의미	: reference에 대한 이해 부족입니다.
			  1. reference는 객체가 참조되면 다른 객체를 참조할 수 없습니다.
			  2. const reference인 경우에는 참조를 통한 value도 수정할 수 없습니다.
			  3. const pointer는 포인터를 통한 객체 수정은 불가능하나, 참조하는 객체는 변경할 수 있습니다.
*/

#include <iostream>
#include <memory>

int main()
{
	int refer1 = 1;
	int refer2 = 2;
	{
		// C2102 error caution!
		const int& data_refer = refer1;
		
		// C2102 error triggered!
		data_refer = refer2;

		// C2102 error solved!
		int& data_refer = refer1;


		std::cout << refer1;
	}

	int* pointer1 = new int(1);
	int* pointer2 = new int(2);
	{
		const int* data_pointer = pointer1;
		data_pointer = pointer2;

		std::cout << *pointer1;
	}
}