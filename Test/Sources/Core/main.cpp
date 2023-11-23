// Online C++ compiler to run C++ program online
#include <iostream>
#include <fstream>
#include <string>

class GameInstance
{
public:
    void Function()
    {
	    
    }
private:
    uint8_t bIsEnabled : 1;
};

int main() {
    std::string inputString = "This is a class example.";

    // 찾을 부분 문자열
    std::string searchString = "class ";

    // 부분 문자열을 찾음
    size_t found = inputString.find(searchString);

    if (found != std::string::npos) {
        // 찾은 경우, "class " 다음의 부분 문자열을 출력
        size_t startPos = found + searchString.length(); // "class " 다음 위치
        size_t endPos = inputString.find(" ", startPos); // 다음 공백의 위치

        if (endPos != std::string::npos) {
            // "class " 다음부터 공백까지의 부분 문자열 출력
            std::string result = inputString.substr(startPos, endPos - startPos);
            std::cout << "Found: " << result << std::endl;
        }
        else {
            // 다음 공백이 없으면 문자열 끝까지 출력
            std::string result = inputString.substr(startPos);
            std::cout << "Found: " << result << std::endl;
        }
    }
    else {
        // 찾지 못한 경우
        std::cout << "Substring not found" << std::endl;
    }

    return 0;
}