#include <iostream>
#include <locale.h>
using namespace std;

int *parent;

void initial_set(int v) {
	parent[v] = v;
}

int find_set(int v) {
	if (v == parent[v])
		return v;
	return find_set(parent[v]);
}

void merge_sets(int v, int w) {
	v = find_set(v);
	w = find_set(w);
	if (v != w)
		parent[w] = v;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int V, ** costs;
	pair <int, int>* frame;
	cout << "Количество вершин: ";
	cin >> V;
	costs = new int* [V];
	
	for (int с = 0; с < V; с++)
		costs[с] = new int[V];

	cout << "Матрица длин рёбер:" << endl;
	for (int a = 0; a < V; a++)
		for (int b = 0; b < V; b++)
		{
			cin >> costs[a][b];
			if (costs[a][b] == 0)
				costs[a][b] = INT_MAX;
		}

	parent = new int[V];
	frame = new pair<int, int>[V - 1];

	for (int v = 0; v < V; v++)
		initial_set(v);

	for (int count = V - 1; count > 0; count--)
	{
		int min = INT_MAX, idx1, idx2;

		for (int v = 0; v < V; v++)
			for (int w = 0; w < V; w++)
				if (costs[v][w] < min && find_set(v) != find_set(w))
				{
					min = costs[v][w];
					idx1 = v;
					idx2 = w;
				}

		merge_sets(idx1, idx2);
		frame[count - 1].first = idx1;
		frame[count - 1].second = idx2;

		costs[idx1][idx2] = INT_MAX;
		costs[idx2][idx1] = INT_MAX;
	}

	for (int f = V - 2; f >= 0; f--)
	{
		cout << "(" << frame[f].first + 1 << "," << frame[f].second + 1 << ") ";
	}
	cout << endl;
	system("pause");
}