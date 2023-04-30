#pragma once
#include <iostream>
#include <string>

class Comment
{
public:
    /**
     * \brief 파라미터를 출력 및 반환
     * \param value 출력 및 반환 대상
     * \return 파라미터를 반환
     */
    static std::string PrintStringFunction(std::string value)
    {
        std::cout << value << std::endl;

        return value;
    }

    /**
     * \brief 파라미터를 2번 출력 및 반환
     * \param value 출력 대상
     * \return 파라미터 그대로 반환
     */
    static std::string PrintStringFunction2(std::string value)
    {
        std::cout << value << std::endl;
        std::cout << value << std::endl;

        return value;
    }
};
