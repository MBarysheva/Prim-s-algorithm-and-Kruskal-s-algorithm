#include <iostream>
using namespace std;
template <class dataType, class value>
class BinaryHeap {
  pair<dataType, value>* tree; //контейнер дл€ кучи
  int h_size, curr_size; //размеры кучи и текущий
  value curr_sum; //текуща€ сумма

  int Level(int elem) const; //ищем уровень в графе
  void toPrev(int elem); //возвращаемс€ наверх
  void toNext(int elem); //идем к потомку
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
    int size)  //создаем кучу заданного массива заданного размера
{
  if (size <= 0) throw size;

  h_size = size;
  curr_size = 0;
  curr_sum = 0;
  tree = new pair<dataType, value>[h_size];  //пара ключ, объект
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
    const  //пор€док уровней, считаем вообще количество потомков, типа у каждого
           //предка дб два потомка, поэтому берем 2^количество уровней в дереве
{
  int level{0};

  for (int i = 1; i <= elem; i += pow(2, level)) level++;

  return level;
}
//дл€ копировани€ поддерева с заданным индексом
template <class dataType, class value>
void BinaryHeap<dataType, value>::toNext(int elem) {
  while (2 * elem + 1 < curr_size) {
    int left = 2 * elem +
               1;  //формула из гиксфогикс, левый потомок или правый потомок
    int right = 2 * elem + 2;

    if (right >= curr_size) right = left;
    // ћетод дл€ создани€ кучи поддерева с корнем по заданному индексу
    // Ётот метод предполагает, что поддеревь€ уже заполнены кучей
    if (tree[left].second < tree[elem].second ||
        tree[right].second < tree[elem].second) {
      int newelem;
      if (tree[left].second < tree[elem].second &&
          tree[left].second < tree[right].second)
        newelem = left;  //самый маленький элемент обновл€етс€
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
         tree[(elem - 1) / 2].second)  //пока меньше предка
  {
    swap(tree[elem],
              tree[(elem - 1) / 2]);  //измен€ем свойство минимальной
                                                //кучи, если оно нарушено
    elem = (elem - 1) / 2;  //уменьшаем значение индекса

    if (elem == 0) break;
  }
}

template <class dataType, class value>
void BinaryHeap<dataType, value>::insertElem(
    pair<dataType, value> newElem) {
  if (curr_size == h_size)
    allocation();  //если размер каррента равен уже размеру кучи, то не можем
                   //вставить ключ

  tree[curr_size++] =
      newElem;  //двигает элемент, а не значение, ссылка в закладках
  curr_sum += newElem.second;

  toPrev(curr_size - 1);
}

template <class dataType, class value>
pair<dataType, value> BinaryHeap<dataType, value>::deleteElem(
    int elem)  // —охран€ем минимальное значение и удал€ем его из кучи, сначала
                // уменьшаем его значение до минус бесконечность, а потом
                // удал€ем мин элемент
{
  if (elem >= curr_size) throw elem;

  curr_sum -= tree[elem].second;

  pair<dataType, value> deletingElem = tree[elem];
  tree[elem] = tree[--curr_size];

  if (curr_size > 1) toNext(elem);

  return deletingElem;
}

template <class dataType, class value> //смотрим текущий размер 
int BinaryHeap<dataType, value>::getSize() const {
  return curr_size;
}

template <class dataType, class value> //ищем корень
pair<dataType, value> BinaryHeap<dataType, value>::getHead() {
  if (curr_size == 0) throw 0;

  return tree[0];
}

template <class dataType, class value> //распредел€ем пам€ть
void BinaryHeap<dataType, value>::allocation() { 
  pair<dataType, value>* newHeap =
      new pair<dataType, value>[h_size * 2];

  for (int i = 0; i < h_size; i++) newHeap[i] = tree[i];

  h_size *= 2;
  delete[] tree;
  tree = newHeap;
}
/*ћолодое поколение - это часть пам€ти, в которой все новые данные (объекты)
создаютс€ дл€ распределени€ пространства, и вс€кий раз, когда эта пам€ть
полностью заполн€етс€, остальные данные сохран€ютс€ в сборке мусора.
—тарое или посто€нное поколение - это часть пам€ти кучи, котора€ содержит старые
объекты данных, которые не используютс€ часто или не используютс€ вообще.*/
