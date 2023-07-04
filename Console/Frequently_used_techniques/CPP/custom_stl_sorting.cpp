// 자주쓰는 STL 컨테이너 정렬 및 사용

// pq : 우선순위를 정해서 배열에 담아야하는 경우.
// v  : 인덱스로 빠르게 접근 and 탐색해야 하는 경우.
// h  : 순서없이, 빠르게 key값을 통해 value를 얻어야 하는 경우.

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
struct INT
{
	int value;

	INT() = default;
	INT(int value) : value(value) {  }

	bool operator()(const INT& left, const INT& right)
	{
		return left.value > right.value;
	}
};

bool comparator(const int& left, const int& right)
{
	return left < right;
}

static std::priority_queue<INT, std::vector<INT>, INT> priorityQueue;
static std::vector<int> vector;
static std::unordered_map<std::string, int> hash;

int main()
{
	priorityQueue.push(4);
	priorityQueue.push(10);
	priorityQueue.push(11);
	priorityQueue.push(6);
	priorityQueue.push(1);

	while (!priorityQueue.empty())
	{
		std::cout << priorityQueue.top().value << std::endl;
		priorityQueue.pop();
	}

	std::cout << std::endl;
	std::cout << std::endl;

	vector.push_back(4);
	vector.push_back(10);
	vector.push_back(11);
	vector.push_back(6);
	vector.push_back(1);

	std::sort(vector.begin(), vector.end(), comparator);

	while (!vector.empty())
	{
		std::cout << vector.front() << std::endl;
		vector.erase(vector.begin());
	}

	std::cout << std::endl;
	std::cout << std::endl;

	// 주의 : Key값만 출력된다,
	hash.insert({ "apple", 1 });
	hash.insert({ "banana", 2 });
	hash.insert({ "banana", 3 });
	hash.insert({ "banana", 4 });
	hash.insert({ "banana", 5 });

	for (auto value : hash)
	{
		std::cout << value.second;
	}

	return 0;
}