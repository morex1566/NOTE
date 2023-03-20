#include <iostream>
#include <vector>

struct Count
{
	int zero_count;
	int one_count;

	Count operator+(const Count& count)
	{
		return {this->zero_count + count.zero_count, this->one_count + count.one_count};
	}
};

static int testcase_count;
static std::vector<int> testcase_n;

void solution(int n)
{
	std::vector<Count> buffer;
	buffer.push_back({ 1, 0 });
	buffer.push_back({ 0, 1 });

	for (int i = 2; i < n + 1; i++)
	{
		buffer.push_back(buffer[i - 1] + buffer[i - 2]);
	}

	std::cout << buffer[n].zero_count << " " << buffer[n].one_count;
	std::cout << std::endl;
}

int main()
{
	std::cin >> testcase_count;

	testcase_n.reserve(testcase_count);
	for (int i = 0; i < testcase_count; i++)
	{
		int input;
		std::cin >> input;

		testcase_n.push_back(input);
	}

	for (int i = 0; i < testcase_count; i++)
	{
		solution(testcase_n[i]);
	}

	return 0;
}