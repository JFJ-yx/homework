#include<iostream>
using namespace std;
template<class T>
class MinHeap {
private:
	T* heapArray;
	int CurrentSize;
	int MaxSize;
	void swap(int pos_x, int pos_y);
	void BuildHeap();
public:
	MinHeap(const int n);
	virtual ~MinHeap() {
		delete[]heapArray;
	};
	bool isEmpty();
	bool isLeaf(int pos)const;
	int leftchild(int pos)const;
	int rightchild(int pos)const;
	int parent(int pos)const;
	bool Insert(const T& newNode);
	T& RemoveMin();
	bool Remove(int pos, T& node);
	void SiftUp(int position);
	void SiftDown(int left);
	void print();
	void array();
};
template<class T>
void MinHeap<T>::array()
{
	int count = CurrentSize;
	while (!this->isEmpty()) {
		this->RemoveMin();
	}
	for (int i = 0; i < count; i++) {
		cout << heapArray[i] << " ";
	}
}

template<class T>
void MinHeap<T>::print()
{
	for (int i = 0; i < CurrentSize; i++) {
		cout << heapArray[i] << " ";
	}
}

template<class T>
bool MinHeap<T>::isEmpty()
{
	if (CurrentSize == 0)
		return true;
	else
		return false;
}

template<class T>
void MinHeap<T>::swap(int pos_x, int pos_y)
{
	T temp = heapArray[pos_x];
	heapArray[pos_x] = heapArray[pos_y];
	heapArray[pos_y] = temp;
}


template<class T>
MinHeap<T>::MinHeap(const int n) {
	if (n <= 0)
		return;
	CurrentSize = 0;
	MaxSize = n;
	heapArray = new T[MaxSize];
	BuildHeap();
}

template<class T>
bool MinHeap<T>::isLeaf(int pos)const {
	return (pos >= CurrentSize / 2) && (pos < CurrentSize);
}

template<class T>
int MinHeap<T>::leftchild(int pos)const {
	return 2 * pos + 1;
}

template<class T>
int MinHeap<T>::rightchild(int pos)const {
	return 2 * pos + 2;
}

template<class T>
int MinHeap<T>::parent(int pos) const
{
	return (pos - 1) / 2;
}

template<class T>
void MinHeap<T>::SiftUp(int position)
{
	int temppos = position;
	T temp = heapArray[temppos];
	while ((temppos > 0) && (heapArray[parent(temppos)] > temp)) {
		heapArray[temppos] = heapArray[parent(temppos)];
		temppos = parent(temppos);
	}
	heapArray[temppos] = temp;
}
template<class T>
void MinHeap<T>::SiftDown(int left)
{
	int i = left;
	int j = leftchild(i);
	T temp = heapArray[i];
	while (j < CurrentSize) {
		if ((j + 1 < CurrentSize) && (heapArray[j] > heapArray[j + 1]))
			j++;
		if (temp > heapArray[j]) {
			heapArray[i] = heapArray[j];
			i = j;
			j = leftchild(j);
		}
		else
			break;
	}
	heapArray[i] = temp;
}
template<class T>
void MinHeap<T>::BuildHeap()
{
	for (int i = (CurrentSize / 2 - 1); i >= 0; i--) {
		SiftDown(i);
	}
}

template<class T>
bool MinHeap<T>::Insert(const T& newNode)
{
	if (CurrentSize == MaxSize)
		return false;
	heapArray[CurrentSize] = newNode;
	SiftUp(CurrentSize);
	CurrentSize++;
	return true;
}

template<class T>
T& MinHeap<T>::RemoveMin()
{
	if (CurrentSize == 0) {
		cout << "can't Delete";
		exit(1);
	}
	else {
		swap(0, --CurrentSize);
		if (CurrentSize > 1)
			SiftDown(0);
		return heapArray[CurrentSize];
	}
}

template<class T>
bool MinHeap<T>::Remove(int pos, T& node)
{
	if ((pos < 0) || (pos >= CurrentSize))
		return false;
	node = heapArray[pos];
	heapArray[pos] = heapArray[--CurrentSize];
	if (heapArray[parent(pos)] > heapArray(pos))
		SiftUp(pos);
	else SiftDown(pos);
	return true;
}