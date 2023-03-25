#include <iostream>
#include <vector>

static int n;
static std::vector<int> buffer;

int fibo(int n)
{
	if (n == 0)
	{
		return buffer[0];
	}
	if (n == 1)
	{
		return buffer[1];
	}

	for (int i = 2; i < n + 1; i++)
	{
		buffer.push_back(buffer[i - 1] + buffer[i - 2]);
	}

	return buffer[n];
}

int main()
{
	int n;

	std::cin >> n;

	buffer.push_back(0);
	buffer.push_back(1);

	std::cout << fibo(n);
}