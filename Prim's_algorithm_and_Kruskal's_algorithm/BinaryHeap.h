#include <iostream>
using namespace std;
template <class dataType, class value>
class BinaryHeap {
  pair<dataType, value>* tree; //��������� ��� ����
  int h_size, curr_size; //������� ���� � �������
  value curr_sum; //������� �����

  int Level(int elem) const; //���� ������� � �����
  void toPrev(int elem); //������������ ������
  void toNext(int elem); //���� � �������
  void allocation(); 

 public:
  BinaryHeap(int size = 100);
  BinaryHeap(const BinaryHeap& copyHeap);
  ~BinaryHeap();
  void insertElem(pair<dataType, value> newElem);
  pair<dataType, value> deleteElem(int elem);
  pair<dataType, value> getHead();
  int getSize() const;
  friend ostream& operator<<(ostream& out, const BinaryHeap<dataType, value>& heap) 
  {
    int lastLevel = 0;
    for (int i = 0; i < heap.curr_size; i++) {
      if (heap.Level(i) != lastLevel) {
        lastLevel = heap.Level(i);
        out << endl;
      }
      out << heap.tree[i].first << ',' << heap.tree[i].second
          << ' ';
    }

    return out;
  }
};

template <class dataType, class value>
BinaryHeap<dataType, value>::BinaryHeap(
    int size)  //������� ���� ��������� ������� ��������� �������
{
  if (size <= 0) throw size;

  h_size = size;
  curr_size = 0;
  curr_sum = 0;
  tree = new pair<dataType, value>[h_size];  //���� ����, ������
}

template <class dataType, class value>
BinaryHeap<dataType, value>::BinaryHeap(
    const BinaryHeap<dataType, value>& copyHeap) {
  h_size = copyHeap.h_size;
  curr_size = copyHeap.curr_size;
  curr_sum = copyHeap.curr_sum;

  tree = new pair<dataType, value>[h_size];
  for (int i = 0; i < curr_size; i++)
    tree[i] = copyHeap.tree[i];
}

template <class dataType, class value>
BinaryHeap<dataType, value>::~BinaryHeap() {
  delete[] tree;
}

template <class dataType, class value>
int BinaryHeap<dataType, value>::Level(int elem)
    const  //������� �������, ������� ������ ���������� ��������, ���� � �������
           //������ �� ��� �������, ������� ����� 2^���������� ������� � ������
{
  int level{0};

  for (int i = 1; i <= elem; i += pow(2, level)) level++;

  return level;
}
//��� ����������� ��������� � �������� ��������
template <class dataType, class value>
void BinaryHeap<dataType, value>::toNext(int elem) {
  while (2 * elem + 1 < curr_size) {
    int left = 2 * elem +
               1;  //������� �� ����������, ����� ������� ��� ������ �������
    int right = 2 * elem + 2;

    if (right >= curr_size) right = left;
    // ����� ��� �������� ���� ��������� � ������ �� ��������� �������
    // ���� ����� ������������, ��� ���������� ��� ��������� �����
    if (tree[left].second < tree[elem].second ||
        tree[right].second < tree[elem].second) {
      int newelem;
      if (tree[left].second < tree[elem].second &&
          tree[left].second < tree[right].second)
        newelem = left;  //����� ��������� ������� �����������
      else
        newelem = right;

      swap(tree[newelem], tree[elem]);
      elem = newelem;
    } else
      break;
  }
}

template <class dataType, class value>
void BinaryHeap<dataType, value>::toPrev(int elem) {
  while (tree[elem].second <
         tree[(elem - 1) / 2].second)  //���� ������ ������
  {
    swap(tree[elem],
              tree[(elem - 1) / 2]);  //�������� �������� �����������
                                                //����, ���� ��� ��������
    elem = (elem - 1) / 2;  //��������� �������� �������

    if (elem == 0) break;
  }
}

template <class dataType, class value>
void BinaryHeap<dataType, value>::insertElem(
    pair<dataType, value> newElem) {
  if (curr_size == h_size)
    allocation();  //���� ������ �������� ����� ��� ������� ����, �� �� �����
                   //�������� ����

  tree[curr_size++] =
      newElem;  //������� �������, � �� ��������, ������ � ���������
  curr_sum += newElem.second;

  toPrev(curr_size - 1);
}

template <class dataType, class value>
pair<dataType, value> BinaryHeap<dataType, value>::deleteElem(
    int elem)  // ��������� ����������� �������� � ������� ��� �� ����, �������
                // ��������� ��� �������� �� ����� �������������, � �����
                // ������� ��� �������
{
  if (elem >= curr_size) throw elem;

  curr_sum -= tree[elem].second;

  pair<dataType, value> deletingElem = tree[elem];
  tree[elem] = tree[--curr_size];

  if (curr_size > 1) toNext(elem);

  return deletingElem;
}

template <class dataType, class value> //������� ������� ������ 
int BinaryHeap<dataType, value>::getSize() const {
  return curr_size;
}

template <class dataType, class value> //���� ������
pair<dataType, value> BinaryHeap<dataType, value>::getHead() {
  if (curr_size == 0) throw 0;

  return tree[0];
}

template <class dataType, class value> //������������ ������
void BinaryHeap<dataType, value>::allocation() { 
  pair<dataType, value>* newHeap =
      new pair<dataType, value>[h_size * 2];

  for (int i = 0; i < h_size; i++) newHeap[i] = tree[i];

  h_size *= 2;
  delete[] tree;
  tree = newHeap;
}
/*������� ��������� - ��� ����� ������, � ������� ��� ����� ������ (�������)
��������� ��� ������������� ������������, � ������ ���, ����� ��� ������
��������� �����������, ��������� ������ ����������� � ������ ������.
������ ��� ���������� ��������� - ��� ����� ������ ����, ������� �������� ������
������� ������, ������� �� ������������ ����� ��� �� ������������ ������.*/
