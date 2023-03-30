/*
	LNK2005	: ~에 이미 정의되어 있습니다.
	해결	: static or inline static or inline keyword를 통해 해결한다.
	의미	: header에 정의한 메서드를 utility function 처럼 사용하려는 경우,
			  include 시에 생기는 중복에러를 피하기 위해 static이나 inline키워드를 사용합니다.
*/

#include <string>
#include <Windows.h>

namespace utilities
{
	// LNK2005 error solved!
	static inline LPCWSTR StringToLPCWSTR(const std::string& str)
	{
		int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
		wchar_t* buffer = new wchar_t[length];
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, length);

		return buffer;
	}
}