#include <iostream>
#include<queue>
using namespace std;

//包含队列的类定义


//包含栈的类定义
template <class T>
class Stack {
public:
	Stack(int MaStackSize = 10);
	~Stack() { delete[] stack; }
	bool IsEmpty() const { return top == -1; }
	bool IsFull() const { return top == MaxTop; }
	T Top() const;
	Stack<T>& Add(const T& x);
	Stack<T>& Delete(T& x);
	void MakeEmpty() { top = -1; } //清空栈
private:
	int top;//栈顶
	int MaxTop;//最大的栈顶值
	T* stack;//堆栈元素数组
};
template<class T>
Stack<T>::Stack(int MaxStackSize)
{
	MaxTop = MaxStackSize - 1;
	stack = new T[MaxStackSize];
	top = -1;
}

template<class T>
T Stack<T>::Top() const
{
	if (IsEmpty())
	{
		cout << "no element"; return false;
	}
	else
		return stack[top];
}
template<class T>
Stack<T>& Stack<T>::Add(const T& x)
{
	if (IsFull())
	{
		cout << "no memory;" << endl; return *this;
	}
	top = top + 1;
	stack[top] = x;
	return *this;
}
template<class T>
Stack<T>& Stack<T>::Delete(T& x)
{
	if (IsEmpty())
	{
		cout << "no element" << endl; return *this;
	}
	x = stack[top];
	top = top - 1;
	return *this;
}
template<class T>
class BinaryTree;
//二叉搜索树节点定义
template <class T>
class BinaryTreeNode
{
	friend class BinaryTree<T>;
public:

	T data;
	BinaryTreeNode* LeftChild, * RightChild;
	BinaryTreeNode(T e) { data = e; LeftChild = 0; RightChild = 0; }

};
//二叉搜索树定义
template <class T>
class BinaryTree
{
public:

	BinaryTreeNode<T>* root;
	BinaryTree() { root = 0; }

	void LevelOrder();//逐层遍历
	BinaryTreeNode<T>* Search(const T& key);//查找
	void Insert(const T& value);//插入
	bool DeleteByCopying(const T& value);//删除
};


//二叉搜索树插入节点
template <class T>
void BinaryTree<T>::Insert(const T& value)
{
	//给出代码
	if (this->root == 0) {
		this->root = new BinaryTreeNode<T>(value);
	}
	else {
		BinaryTreeNode<T>* temp = root;
		BinaryTreeNode<T>* p = NULL;
		bool isleft;
		while (temp != 0) {
			p = temp;
			if (temp->data > value) {
				temp = temp->LeftChild;
				isleft = true;
			}
			else {
				temp = temp->RightChild;
				isleft = false;
			}
		}
		if (isleft)
			p->LeftChild = new BinaryTreeNode<T>(value);
		else
			p->RightChild = new BinaryTreeNode<T>(value);
	}
}

//二叉搜索树查找节点
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::Search(const T& key)
{
	//给出代码
	BinaryTreeNode<T>* temp = root;
	while (temp != 0&&temp->data!=key) {
		if (temp->data > key) 
			temp = temp->LeftChild;
		else
			temp = temp->RightChild;
	}
	if (temp)
		return temp;
	else
		return NULL;
}

//二叉搜索树删除节点
template <class T>
bool BinaryTree<T>::DeleteByCopying(const T& value)
{
	//给出代码
	if (this->Search(value) == NULL)
		return false;
	else {
		BinaryTreeNode<T>* t = this->Search(value);
		BinaryTreeNode<T>* temp = t;
		BinaryTreeNode<T>* p = 0;
		if (t->LeftChild)
			temp = temp->LeftChild;
		while (temp->RightChild != 0) {
			p = temp;
			temp = temp->RightChild;
		}
		t->data = temp->data;
		if (temp->LeftChild)
			p->RightChild = temp->LeftChild;
		delete temp;
		return true;
	}
}

//逐层遍历
//打印时，假设p为当前需要访问的结点，循环中cout<<p->data<<" ";  在全部打印完成之后，cout<<endl;
template <class T>
void BinaryTree<T>::LevelOrder()
{
	//给出代码
	queue<BinaryTreeNode<T>*> q;
	BinaryTreeNode<T>* temp = root;
	q.push(temp);
	while (!q.empty()) {
		BinaryTreeNode<T>* p;
		p = q.front();
		if(p->LeftChild)
			q.push(p->LeftChild);
		if(p->RightChild)
			q.push(p->RightChild);
		cout << p->data << " ";
		q.pop();
	}
	cout << endl;
}

int main()
{
	BinaryTree<int> bt;
	BinaryTreeNode<int>* tmp;
	bt.Insert(400);
	bt.Insert(122);
	bt.Insert(450);
	bt.Insert(99);
	bt.Insert(250);
	bt.Insert(500);
	bt.Insert(110);
	bt.Insert(200);
	bt.Insert(300);
	bt.Insert(105);
	bt.Insert(330);       //插入建立二叉搜索树
	bt.LevelOrder();      //层次遍历
	if (bt.DeleteByCopying(122))	//删除值为122的节点
	{
		cout << "successful" << endl;
	}
	else
	{
		cout << "failed" << endl;
	}
	bt.LevelOrder();
	tmp = bt.Search(4);       //查找值为4的节点
	if (tmp != NULL)
		cout << "successful" << endl;
	else
		cout << "failed" << endl;
	bt.Insert(5);			//插入5
	bt.LevelOrder();
	return 0;
}