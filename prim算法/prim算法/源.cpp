#include<iostream>
#include<cstring>
#include<string> 
using namespace std;
const int MaxSize = 100;
const int MAX = 9999;

class MGraph
{
	string vertex[MaxSize];   //图的顶点信息 
	int adj[MaxSize][MaxSize];    //图的邻接矩阵 
	int vertexNum, edgeNum;
public:
	MGraph(int n);
	void print();
	int W(int i, int j);
	void InsertEdge(int i, int j, int p);
	int VexNum()
	{
		return vertexNum;
	}
	friend void Prim(MGraph& g, int u0);
};

void MGraph::print()
{
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < vertexNum; j++) {
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}
}

MGraph::MGraph(int n)
{
	vertexNum = n;
	edgeNum = 0;
   //将邻接矩阵所有元素赋为0 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				adj[i][j] = 0;
			else
				adj[i][j] = MAX;
		}
	}
}


void MGraph::InsertEdge(int i, int j, int p)   //插入顶点i、j依附的边以及该边的权值 
{
	adj[i][j] = adj[j][i] = p;
	edgeNum++;
}

int MGraph::W(int i, int j)
{
	return adj[i][j];
}

void Prim(MGraph& g, int u0)
{
	int k;
	int n = g.VexNum();
	struct node  //定义一个节点结构体 包含该节点距离生成树各节点最近的节点及其边的权值
	{
		int adjvex;
		int lowcost;
	}closedge[MaxSize];
	closedge[u0].adjvex = u0;
	closedge[u0].lowcost = 0;
	for (int v = 0; v < n; v++)
	{
		if (v != u0)
		{
			closedge[v].adjvex = u0;
			closedge[v].lowcost = g.W(u0, v);
		}
	}
	closedge[u0].lowcost = 0;
	for (int i = 0; i <= n - 2; i++)
	{
		k = 0;
		int minw = MAX;
		for (int v = 0; v <= n - 1; v++)
		{
			if (closedge[v].lowcost > 0 && closedge[v].lowcost < minw)
			{
				k = v;
				minw = closedge[v].lowcost;
			}
		}
		cout << "(" << closedge[k].adjvex << "," << k << ")" << ":" << minw << " " << endl;
		closedge[k].lowcost = 0;   //顶点k并入U集 
		for (int v = 0; v <= n - 1; v++) //更新还没并与U集节点的信息
		{
			if (closedge[v].lowcost != 0 && g.W(k, v) < closedge[v].lowcost)
			{
				closedge[v].lowcost = g.W(k, v);
				closedge[v].adjvex = k;
			}
		}
	}
}

int main()
{
	struct Edge
	{
		int from, end, power;
	};

	int n = 6;   //6个顶点 
	int e = 10;
	Edge b[] = { {0,1,6},{0,2,1},{0,3,5},{1,2,5},{1,4,3},{2,3,5},{2,4,6},{2,5,4},{3,5,2},{4,5,6} };
	MGraph m(n);
	for (int k = 0; k < e; k++)m.InsertEdge(b[k].from, b[k].end, b[k].power);  //插入所有边,将邻接矩阵赋值
	cout << "打印出邻接矩阵（9999代表无穷大）" << endl;
	m.print();//打印出邻接矩阵
	cout << "打印出保留下的边" << endl;
	Prim(m, 0);// 打印出保留下的边
	return 0;
}
