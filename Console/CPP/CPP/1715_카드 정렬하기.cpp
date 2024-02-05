#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;


struct CardPack
{
	int count;

	bool operator<(const CardPack& other) const
	{
		return count > other.count;
	}
};

static priority_queue<CardPack> Pack;

int main()
{
	int cardPackSize = 0;
	std::cin >> cardPackSize; 
	for (int i = 0; i < cardPackSize; i++)
	{
		int cardCount = 0;
		std::cin >> cardCount;
		
		Pack.push({cardCount});
	}

	int answer = 0;
	while (Pack.size() != 1)
	{
		CardPack np;

		CardPack p1 = Pack.top();
		Pack.pop();
		CardPack p2 = Pack.top();
		Pack.pop();

		np.count = p1.count + p2.count;
		answer += np.count;

		Pack.push(np);
	}

	std::cout << answer;
}