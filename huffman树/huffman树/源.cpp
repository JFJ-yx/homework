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

template<class T>
class HuffmanTreeNode {
public:
	HuffmanTreeNode* right=NULL;
	HuffmanTreeNode* left=NULL;
	HuffmanTreeNode* parent=NULL;
	int element;
	T data;
	bool operator>( HuffmanTreeNode<T>h1) {
		if (this->element > h1.element)
			return true;
		else
			return false;
	}
	bool isleaf() {
		return (this->left == NULL && this->right == NULL);
	}
};

template<class T>
class HuffmanTree {
private:
	HuffmanTreeNode<T>* root;
	T* t1;
	string* s1;
	void MergeTree(HuffmanTreeNode<T>* ht1, HuffmanTreeNode<T>* ht2, HuffmanTreeNode<T>* parent);
	void DeleteTree(HuffmanTreeNode<T>* root);
public:
	HuffmanTree(int weight[], int n,T *c);//weight是权重的数组，n是数组长度
	virtual ~HuffmanTree() {
		DeleteTree(root);
	}
	HuffmanTreeNode<T>* reroot() {
		return this->root;
	}

	void preorder(HuffmanTreeNode<T>* root) {
		if (root != NULL) {
			cout << root->element << " ";
			preorder(root->left);
			preorder(root->right);
		}
	}
	void bianli(HuffmanTreeNode<T>* root, HuffmanTreeNode<T>* p, string str, T* a, int& j) {
		HuffmanTreeNode<T>* q = p;
		int i, n;
		if (q == NULL) {
			return;
		}
		if (q->isleaf()) {
			cout << str << " ";
			a[j] = q->data;
			this->s1[j] = str;
			this->t1[j] = q->data;
			j++;
			return;
		}
		string temp = str;
		str += "0";
		bianli(root, q->left, str, a, j);
		temp += "1";
		bianli(root, q->right, temp, a, j);

	}
	void bianma(string s) {
		int j = 0;
		for (int i = 0; i < s.length(); i++) {
			for (;; j++) {
				if (s[i] == this->t1[j]){
					cout << this->s1[j] << " ";
					j = 0;
					break;
				}
					
			}
		}
	}
	void encode() {
		int j = 0;
		T a[10];
		string str = "";
		bianli(root, root, str, a, j);
		cout << endl;
		for (int i = 0; i < j; i++) 
			cout << a[i] << " ";
		cout << endl;
	}
	void yima(string s) {
		HuffmanTreeNode<T>* q = root;
		int counter = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '0') {
				q = q->left;
			}
			else
				q = q->right;
			if (q->isleaf()) {
				cout << q->data;
				q = root;
			}
		}
		cout << endl;
	}
};

template<class T>
void HuffmanTree<T>::DeleteTree(HuffmanTreeNode<T>* root)
{
	HuffmanTreeNode<T>* r = root;
	if (r->left)
		DeleteTree(r->left);
	if (r->right)
		DeleteTree(r->right);
	delete r;
}

template<class T>
void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T>* ht1, HuffmanTreeNode<T>* ht2, HuffmanTreeNode<T>* parent)
{
	parent->left = ht1;
	parent->right = ht2;
	parent->data = 0;
	parent->element = ht1->element + ht2->element;
	parent->parent = NULL;
	ht1->parent = ht2->parent = parent;
	
}

template<class T>
HuffmanTree<T>::HuffmanTree(int weight[], int n,T *c)
{
	this->t1 = new T[n];
	this->s1 = new string[n];
	MinHeap<HuffmanTreeNode<T>> heap(n);
	HuffmanTreeNode<T>* parent=NULL,  firstchild,  secondchild;
	HuffmanTreeNode<T>* Nodelist = new HuffmanTreeNode<T>[n];
	for (int i = 0; i < n; i++) {
		(Nodelist[i]).element = weight[i];
		Nodelist[i].parent = Nodelist[i].left = Nodelist[i].right = NULL;
		Nodelist[i].data = c[i];
		heap.Insert(Nodelist[i]);
	}
	for (int i = 0; i < n - 1; i++) {
		parent = new HuffmanTreeNode<T>;
		firstchild = heap.RemoveMin();
		secondchild = heap.RemoveMin();
		HuffmanTreeNode<T>* Firstchild = new HuffmanTreeNode<T>;
		HuffmanTreeNode<T>* Secondchild = new HuffmanTreeNode<T>;
		*Firstchild = firstchild;
		*Secondchild = secondchild;
		MergeTree(Firstchild, Secondchild, parent);		
		heap.Insert(*parent);
		root = parent;

	}
	delete []Nodelist;
}
int main() {
	int t[5] = { 7,5,6,9,4 };
	char c[5] = { 'a','b','c','d','e' };
	HuffmanTree<char> h1(t, 5,c);
	h1.encode();
	string s;
	cin >> s;
	h1.yima(s);
	string o;
	cin >> o;
	h1.bianma(o);
	return 0;
}
