#include<iostream>
#include<string>

using namespace std;
int root[2000];
string tree = "";
struct edge
{
	int begin;
	int end;
	int weight;
};
typedef edge* Edge;
struct graph
{
	int vn;
	int en;
	Edge data;
};

void init(graph* obj);
int seek_root(int v);
void quick_sort(graph* obj, int front, int back);
int qs(graph* obj, int front, int back);
int Kruskal(graph* g);

void init(graph* obj)
{
	cout << "请输入顶点和边的个数:" << endl;
	cin >> obj->vn >> obj->en;
	obj->data = new edge[obj->en];
	cout << "输入边的起点  终点   权重" << endl;
	for (int i = 0; i < obj->en; ++i)
	{
		int x, y;
		cin >> x >> y >> obj->data[i].weight;
		if (x < y) { obj->data[i].begin = x; obj->data[i].end = y; }
		else { obj->data[i].begin = y; obj->data[i].end = x; }
	}
	for (int j = 0; j < obj->vn; ++j)
		root[j] = j;
}

int seek_root(int v)
{
	while (root[v] != v)
		v = root[v];
	return v;
}

void quick_sort(graph* obj, int front, int back)
{
	if (front > back)
		return;
	int mid = qs(obj, front, back);
	quick_sort(obj, front, mid - 1);
	quick_sort(obj, mid + 1, back);
}

int qs(graph* obj, int front, int back)
{
	int temp = back;
	while (front < back)
	{
		while (front < back && obj->data[front].weight <= obj->data[temp].weight)
			++front;
		while (front < back && obj->data[back].weight >= obj->data[temp].weight)
			--back;
		swap(obj->data[front], obj->data[back]);
	}
	swap(obj->data[front], obj->data[temp]);
	return front;
}

int Kruskal(graph* g)
{
	int mintree = 0;
	for (int i = 0; i < g->en; ++i)
	{
		int x = seek_root(g->data[i].begin);
		int y = seek_root(g->data[i].end);
		if (x != y)
		{
			root[g->data[i].end] = x;
			mintree += g->data[i].weight;
			tree += to_string(g->data[i].begin) + "-" + to_string(g->data[i].end) + " ";
		}
	}
	return mintree;
}

int main()
{
	memset(root, 0, sizeof(root));
	graph* g = new graph;
	init(g);
	quick_sort(g, 0, g->en - 1);
	cout << "结果为：" << Kruskal(g) << endl;
	cout << tree << endl;
	delete g;
	return 0;
}