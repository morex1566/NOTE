#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int number = 6;
int INF = 100000000;
vector<pair<int, int>> a[7];
int d[7];

void dijkstra(int start)
{
	d[start] = 0;
	priority_queue<pair<int,int>> pq;
	pq.push(make_pair(start, 0));

	while (!pq.empty())
	{
		int current_index = pq.top().first;
		int distance = -pq.top().second;

		pq.pop();
		if (d[current_index] < distance) { continue; }

		for (int i = 0; i < a[current_index].size(); i++)
		{
			int selected_node = a[current_index][i].first;
			int selected_distance = distance + a[current_index][i].second;

			if (d[selected_node] > selected_distance)
			{
				d[selected_node] = selected_distance;
				pq.push(make_pair(selected_node, -selected_distance));
			}
		}
	}
}

int main()
{
	// 그래프정보를 초기화 합니다. 
	// + 기본적으로 연결되지 않았다면 INF로 초기화 됩니다.
	// + 0번째 index는 편의상 사용하지 않습니다.
	{
		for (int i = 1; i < number; i++) { d[i] = INF; }
	}

	a[1].push_back(make_pair(2, 2));
	a[1].push_back(make_pair(3, 5));
	a[1].push_back(make_pair(4, 1));

	a[2].push_back(make_pair(1, 2));
	a[2].push_back(make_pair(3, 3));
	a[2].push_back(make_pair(4, 2));

	a[3].push_back(make_pair(1, 5));
	a[3].push_back(make_pair(2, 3));
	a[3].push_back(make_pair(4, 3));
	a[3].push_back(make_pair(5, 1));
	a[3].push_back(make_pair(6, 5));

	a[4].push_back(make_pair(1, 1));
	a[4].push_back(make_pair(2, 2));
	a[4].push_back(make_pair(3, 3));
	a[4].push_back(make_pair(5, 1));

	a[5].push_back(make_pair(3, 1));
	a[5].push_back(make_pair(4, 1));
	a[5].push_back(make_pair(6, 2));

	a[6].push_back(make_pair(3, 5));
	a[6].push_back(make_pair(5, 2));

	dijkstra(1);

	for (int i = 1; i <= number; i++)
	{
		std::cout << d[i] << " ";
	}
}