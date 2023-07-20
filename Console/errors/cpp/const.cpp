// notice : r-value는 수정할 수 없다.

// example case
int ReturnFour()
{
    return 4;
}

int main()
{
    int&       data1 = ReturnFour(); // E0461
    const int& data2 = ReturnFour();

    return 0;
}