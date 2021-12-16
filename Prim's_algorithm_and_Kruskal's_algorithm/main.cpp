#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include <locale.h>
#include "BinaryHeap.h"
#include "TimeRealise.h"

using namespace std;
void initial_set(int v) {
  int* parent = 0;
  parent[v] = v;
}
int find_set(int v) {
  int* parent = 0;
  if (v == parent[v]) return v;
  return find_set(parent[v]);
}
void merge_sets(int v, int w) {
  int* parent = 0;
  v = find_set(v);
  w = find_set(w);
  if (v != w) parent[w] = v;
}
int min(set<int>& heap, int* key) {
  int min = INT_MAX;
  int index;
  for (auto h : heap)
    if (key[h] < min) {
      min = key[h];
      index = h;
    }
  return index;
}
class Graf {
  int** graf; //взяли граф
  int V, E; //к нему ребра и вершины
  pair<int, int>* E_set; //хранилище для ребер
  BinaryHeap<int, int>* E_heap; //и кучу для них 

 public: 
  Graf(int vC = 0, int eC = 0, int minWeight = 0, int maxWeight = 0)
      : V(vC), E(min(eC, V * (V - 1) / 2)) {
    int freeEdge = 0;
    E_set = new pair<int, int>[E];

    graf = new int*[V - 1];
    E_heap = new BinaryHeap<int, int>[V] { V };

    random_device dev;
    mt19937 gen(dev());
    uniform_real_distribution<> urd(
        minWeight, maxWeight);  //рандомно создаем массивы чисел рандом
    for (int i = 0; i < V - 1; i++) {
      graf[i] = new int[V - i - 1]{0};
      for (int j = 0; j < V - 1 - i && freeEdge < E; j++) {
        int weight = static_cast<int>(urd(gen));  //ген сл чиселок
        weight = weight <= 0 ? 1 : weight;

        graf[i][j] = weight;
        E_set[freeEdge] = {i, j};
        E_heap[i].insertElem({j + i + 1, weight});
        E_heap[j + i + 1].insertElem({i, weight});
        freeEdge++;
      }
    }
  }
  Graf(const Graf& copyGraf) : V(copyGraf.V), E(copyGraf.E) {
    int freeEdge = 0;
    E_set = new pair<int, int>[E];

    graf = new int*[V - 1];
    E_heap = new BinaryHeap<int, int>[V - 1] { V };
    for (int i = 0; i < V - 1; i++) {
      graf[i] = new int[V - i - 1]{0};
      for (int j = 0; j < V - 1 - i && freeEdge < E; j++) {
        graf[i][j] = copyGraf.graf[i][j];
        E_set[freeEdge] = {i, j};
        E_heap[i].insertElem({j, graf[i][j]});
        freeEdge++;
      }
    }
  }
  ~Graf() {
    for (int i = 0; i < V - 1; i++) delete[] graf[i];
    delete[] graf;
    delete[] E_set;
    delete[] E_heap;
  }
  int weight(int v1, int v2) const {
    if (v1 >= V || v2 >= V)
      throw V;
    else if (v1 == v2)
      return 0;
    else if (v1 > v2)
      return graf[v2][--v1 - v2];
    else
      return graf[v1][--v2 - v1];
  }
  void back() 
  {
    delete[] E_heap;
    E_heap = new BinaryHeap<int, int>[V - 1];

    int freeEdge = 0;
    for (int i = 0; i < V - 1; i++) {
      for (int j = 0; j < V - 1 - i && freeEdge < E; j++) {
        E_heap[i].insertElem({j + i + 1, graf[i][j]});
        E_heap[j + i + 1].insertElem({i, graf[i][j]});
        freeEdge++;
      }
    }
  }  //функция возвр 
  pair<vector<pair<int, int>>, int> KruskalAlgorithm();
  pair<vector<pair<int, int>>, int> PrimAlgorithm();
};


pair<vector<pair<int, int>>, int> Graf::KruskalAlgorithm() {
  vector<pair<int, int>> res;
  vector<vector<int>> frame;//группа деревьев
  vector<int> cs(V, 0); //комп св
  int sum{0};
  int end{0}, pV{1}; //конечная группа, текущая вершина

  sort(E_set, E_set + E, [&](pair<int, int> a, pair<int, int> b) { //объед комп связности
  return graf[a.first][a.second] < graf[b.first][b.second];});

  for (int i = 0; i < E && pV < V; i++) {
    int v1 = E_set[i].first,
        v2 = E_set[i].second + 1 + v1;

    if (cs[v1] != cs[v2] ||(cs[v1] == 0 || cs[v2] == 0))
    {
      res.push_back(E_set[i]);
      if (cs[v1] == 0 &&
          cs[v2] == 0) 
      {
        cs[v2] = ++end;
        cs[v1] = end;
        frame.push_back(vector<int>{v1, v2}); //пока верш не соед все кс вносим в ребро меж верш

      } 
      else if (cs[v1] == 0) //объед кс
      {
        cs[v1] = cs[v2];
        frame[cs[v2] - 1].push_back(v1);
      }
      else if (cs[v2] == 0) 
      {
        cs[v2] = cs[v1];
        frame[cs[v1] - 1].push_back(v2);
      }
      else {
        if (frame[cs[v1] - 1].size() < frame[cs[v2] - 1].size()) 
        {
          int new_cs = cs[*(frame[cs[v2] - 1].begin())];
          for (const auto& vert : frame[cs[v1] - 1]) 
          {
            frame[cs[v2] - 1].push_back(vert);
            cs[vert] = new_cs;
          }
        }
        else 
        {
          int new_cs = cs[*(frame[cs[v1] - 1].begin())];
          for (const auto& vert : frame[cs[v2] - 1]) 
          {
            frame[cs[v1] - 1].push_back(vert);
            cs[vert] = new_cs;
          }
        }
      }
      sum += graf[v1][E_set[i].second];
      pV++;
    }
  }
  return pair<vector<pair<int, int>>, int>{res, sum};
}

pair<vector<pair<int, int>>, int> Graf::PrimAlgorithm() 
{
  pair<vector<pair<int, int>>, int> res;
  set<int> blockedVertex;

  pair<int, int> startdge = E_heap[0].getHead();

  res.first.push_back({0, startdge.first});
  res.second += startdge.second;
  blockedVertex.insert(0);

  blockedVertex.insert(startdge.first);

  while (blockedVertex.size() != V) {
    BinaryHeap<pair<int, int>, int> temporaryHeap(V);

    for (auto it : blockedVertex) {
      while (E_heap[it].getSize() > 0 && blockedVertex.find(E_heap[it].getHead().first) != blockedVertex.end()) //если все пройдено и края нет
      {
        E_heap[it].deleteElem(0);
      }

      if (E_heap[it].getSize() > 0) //если посещены не все, наход новый мин вес
      {
        temporaryHeap.insertElem({{it, E_heap[it].getHead().first},  E_heap[it].getHead().second});
      }
    }

    pair<pair<int, int>, int> newElem = temporaryHeap.deleteElem(0);

    blockedVertex.insert(newElem.first.second);
    res.first.push_back({newElem.first.first, newElem.first.second});
    res.second += newElem.second;
  }

  return res;
}
int main()
{
  int i = 0;
  setlocale(LC_ALL, "Russian");
  cout << "Выберите:\n 1)Запустить тест \n 2) Выйти\n";
  cin >> i;
  switch (i) 
  {
    case 1: {
      ofstream kruskalData("../KruskalTest.txt");
      ofstream primData("../PrimTest.txt");
      int V, E, start, step;
      cout << "Количество вершин: ";
      cin >> V;
      cout << "Количество ребер: ";
      cin >> E;
      cout << "Стартовое ребро: ";
      cin >> start;
      cout << "Шаг: ";
      cin >> step;

      kruskalData << V << ' ' << E << ' ' << start << ' ' << step;
      primData << V << ' ' << E << ' ' << start << ' ' << step;

      GrafTest::time time;
      for (int i = start; i <= E; i += step) {
        Graf testGraf(V, i, -1000, 1000);

        time.resetTime();
        testGraf.KruskalAlgorithm();
        auto kruskalTimeWork = time.getTime();

        time.resetTime();
        testGraf.PrimAlgorithm();
        auto primTimeWork = time.getTime();

        kruskalData << '\n' << kruskalTimeWork;
        primData << '\n' << primTimeWork;
      }
      break;
    }
    case 2: 
    {
      exit(0);
    }
    case 3: {
        int* parent;
        int V, **costs;
        pair<int, int>* frame;
        cout << "Количество вершин: ";
        cin >> V;
        costs = new int*[V];

        for (int с = 0; с < V; с++) costs[с] = new int[V];

        cout << "Матрица длин рёбер:" << endl;
        for (int a = 0; a < V; a++)
          for (int b = 0; b < V; b++) {
            cin >> costs[a][b];
            if (costs[a][b] == 0) costs[a][b] = INT_MAX;
          }

        parent = new int[V];
        frame = new pair<int, int>[V - 1];

        for (int v = 0; v < V; v++) initial_set(v);

        for (int count = V - 1; count > 0; count--) {
          int min = INT_MAX, idx1, idx2;

          for (int v = 0; v < V; v++)
            for (int w = 0; w < V; w++)
              if (costs[v][w] < min && find_set(v) != find_set(w)) {
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

        for (int f = V - 2; f >= 0; f--) {
          cout << "(" << frame[f].first + 1 << "," << frame[f].second + 1
               << ") ";
        }
        cout << endl;
        break;
      }
    case 4: {
        int V, **costs;
        cout << "Количество вершин: ";
        cin >> V;
        costs = new int*[V];
        for (int a = 0; a <= V - 1; a++) {
          costs[a] = new int[V];
        }
        cout << "Матрица длин рёбер:" << endl;
        for (int a = 0; a <= V - 1; a++)
          for (int b = 0; b <= V - 1; b++) {
            cin >> costs[a][b];
            if (costs[a][b] == 0) costs[a][b] = INT_MAX;
          }
        set<int> visited, unvisited, heap;
        set<pair<int, int>> frame;
        visited.insert(0);
        pair<int, int>* winner;
        int* key;
        winner = new pair<int, int>[V];
        key = new int[V];
        for (int v = 1; v <= V - 1; v++) {
          if (costs[0][v] != INT_MAX) {
            key[v] = costs[0][v];
            winner[v] = {0, v};
          } else {
            key[v] = INT_MAX;
            winner[v] = {NULL, NULL};
          }
          heap.insert(v);
          unvisited.insert(v);
        }

        while (heap.size() != 0) {
          int w = min(heap, key);
          heap.erase(w);
          visited.insert(w);
          unvisited.erase(w);
          frame.insert({winner[w].first, winner[w].second});
          for (auto v : unvisited) {
            if (costs[w][v] != INT_MAX && costs[w][v] < key[v]) {
              heap.erase(v);
              key[v] = costs[w][v];
              winner[v] = {w, v};
              heap.insert(v);
            }
          }
        }

        for (auto v : frame) {
          cout << "(" << v.first + 1 << ", " << v.second + 1 << ")"
               << "  ";
        }
        cout << endl;
        break;
      }
  }
}