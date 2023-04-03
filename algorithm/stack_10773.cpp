#include <iostream>

static constexpr int MAX_SIZE = 100000;
static int stack[MAX_SIZE];
static int it = 0;
static int k;

using namespace  std;

int main()
{
    cin >> k;

    for(int i =0; i<k; i++)
    {
        int input;
        cin >> input;

        if(input == 0 && it != 0)
        {
            stack[it] = 0;
            it--;
        }
        else
        {
            stack[it] = input;
            it++;
        }
    }

    int sum =0;
    for(int i=0; i<it; i++)
    {
        sum += stack[i];
    }

    cout << sum;
    
    return 0;
}