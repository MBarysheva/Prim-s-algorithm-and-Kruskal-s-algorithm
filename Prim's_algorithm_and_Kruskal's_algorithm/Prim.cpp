#include <iostream>
#include <set>
using namespace std;

int min(set <int> &heap, int* key)
{
	int min = INT_MAX;
	int index;
	for (auto h : heap)
		if (key[h] < min)
		{
			min = key[h];
			index = h;
		}
	return index;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int V, ** costs;
	cout << "Количество вершин: ";
	cin >> V;
	costs = new int* [V];
	for (int a = 0; a <= V - 1; a++)
	{
		costs[a] = new int[V];
	}
	cout << "Матрица длин рёбер:" << endl;
	for (int a = 0; a <= V - 1; a++)
		for (int b = 0; b <= V - 1; b++)
		{
			cin >> costs[a][b];
			if (costs[a][b] == 0)
				costs[a][b] = INT_MAX;
		}
	set <int> visited, unvisited, heap;
	set <pair <int, int>> frame;
	visited.insert(0);
	pair <int, int>* winner;
	int* key;
	winner = new pair <int, int>[V];
	key = new int[V];
	for (int v = 1; v <= V - 1; v++)
	{
		if (costs[0][v] != INT_MAX)
		{
			key[v] = costs[0][v];
			winner[v] = { 0, v };
		}
		else
		{
			key[v] = INT_MAX;
			winner[v] = { NULL, NULL };
		}
		heap.insert(v);
		unvisited.insert(v);
	}

	while (heap.size() != 0)
	{
		int w = min(heap, key);
		heap.erase(w);
		visited.insert(w);
		unvisited.erase(w);
		frame.insert({ winner[w].first, winner[w].second });
		for (auto v : unvisited)
		{
			if (costs[w][v] != INT_MAX && costs[w][v] < key[v])
			{

				heap.erase(v);
				key[v] = costs[w][v];
				winner[v] = { w, v };
				heap.insert(v);
			}
		}
	}

	for (auto v : frame)
	{
		cout << "(" << v.first + 1 << ", " << v.second + 1 << ")" << "  ";
	}
	cout << endl;
	system("pause");
}