#include <iostream>
#include <vector>

int INF = 11;

int V, E, K;
std::vector<std::vector<int>> graph;
std::vector<bool> visited;
std::vector<int> distance;

// distance�� ���� ���� node�� index�� �����ɴϴ�.
// ����Ž������ �����˴ϴ�.
int getnIndexByMin()
{
	int min = INF;
	int index = 0;

	for (int i = 0; i < V; i++)
	{
		if (!visited[i] && distance[i] < min)
		{
			min = distance[i];
			index = i;
		}
	}

	return index;
}

// ���ͽ�Ʈ�� �˰����� �����մϴ�.
void dijkstra(int start)
{
	int current_index = start - 1;
	visited[current_index] = true;

	for (int i = 0; i < V; i++)
	{
		distance[i] = graph[current_index][i];
	}

	for (int i = 0; i < V - 1; i++)
	{
		int current_index = getnIndexByMin();
		visited[current_index] = true;

		for (int j = 0; j < V; j++)
		{
			if (!visited[j])
			{
				if (distance[j] > graph[current_index][j] + distance[current_index])
				{
					distance[j] = graph[current_index][j] + distance[current_index];
				}
			}
		}
	}
}

int main()
{
	std::cin >> V >> E;
	std::cin >> K;

	// �׷����� �� �� ���� �����̳ʸ� �ʱ�ȭ �մϴ�.
	{
		graph.resize(V);
		for (int i = 0; i < V; i++)
		{
			graph[i].resize(V, INF);
			graph[i][i] = 0;
		}

		for (int i = 0; i < E; i++)
		{
			int u, v, w;
			std::cin >> u >> v >> w;

			graph[u - 1][v - 1] = w;
		}

		visited.resize(V, false);
		distance.resize(V, INF);
	}

	dijkstra(K);

	// ��º� �Դϴ�.
	for (int i = 0; i < V; i++)
	{
		if (distance[i] == INF)
		{
			std::cout << "INF" << std::endl;
		}
		else
		{
			std::cout << distance[i] << std::endl;
		}
	}
}