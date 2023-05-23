#pragma once
#include <iostream>
#include <string>

class LogManager
{
public:
    template <typename... Arg> static void Log(Arg... arg);
};

template <typename ... Arg> void LogManager::Log(Arg... arg)
{
    std::cout << arg << std::endl;
}
