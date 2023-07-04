#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


struct PINT
{
	int first;
	int second;

	PINT() = default;

	PINT(const std::pair<int, int>& pair)
		: first(pair.first), second(pair.second) {}

	PINT(int first, int second)
		: first(first), second(second) {}

	bool operator()(const PINT& left, const PINT& right) const
	{
		return left.second < right.second;
	}
};

static std::priority_queue<PINT, std::vector<PINT>, PINT> queue;

static std::vector<int> vector;

bool comparator(int left, int right)
{
	return left < right;
}

int main()
{
	queue.push(std::pair<int, int>(4, 3));
	queue.push(std::pair<int, int>(4, 8));
	queue.push(std::pair<int, int>(4, 1));
	queue.push(std::pair<int, int>(4, 5));
	queue.push(std::pair<int, int>(4, 10));

	while (!queue.empty())
	{
		std::cout << queue.top().second;
		queue.pop();
	}

	vector.push_back(4);
	vector.push_back(10);
	vector.push_back(1);
	vector.push_back(7);
	vector.push_back(5);

	std::sort(vector.begin(), vector.end(), comparator);

	while(!vector.empty())
	{
		std::cout << vector.back();
		vector.pop_back();
	}
}