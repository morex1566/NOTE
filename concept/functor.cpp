#include <iostream>
#include <future>

using namespace std::chrono_literals;

std::future<int> computeValue()
{
    return std::async(std::launch::async, [] {
        std::this_thread::sleep_for(2s);
        std::cout << "Value: " << 4 << std::endl;
        return 42;
    });
}

std::future<void> printValue(int value)
{
    return std::async(std::launch::async, [value] {
        std::this_thread::sleep_for(1s);
        std::cout << "Value: " << value << std::endl;
    });
}

int main()
{
    auto valueFuture = computeValue();
    auto value = valueFuture.get();

    auto printFuture = printValue(value);
    printFuture.get();

    return 0;
}