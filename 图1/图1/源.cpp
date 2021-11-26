#include<iostream>
#define INFINITY 9999
#define UNVISITED -1
#define VISITED -2
#include<stack>
#include<queue>
using namespace std;

//边类型
class Edge {
public:
	int start, end;
	int weight;
	Edge(){}
};

class AdjGraph {
public:
	int vertexNum;//图顶点数目
	int edgeNum;//图的边数
	int* Mark;
	int** matrix;
	int ToVertex(Edge e) {
		return e.end;
	}
	bool IsEdge(Edge e) {
		if (e.end<0 || e.end>edgeNum || e.start<0 || e.start>edgeNum)
			return false;
		if (matrix[e.start][e.end] == 0 || matrix[e.start][e.end] == INFINITY)
			return false;
		else
			return true;
	}
	AdjGraph(int v) {
		vertexNum = v;
		edgeNum = 0;
		Mark = new int[vertexNum];
		for (int i = 0; i < vertexNum; i++) {
			Mark[i] = UNVISITED;
		}
		int i, j;
		matrix = (int**)new int* [v];
		for (i = 0; i < vertexNum; i++) {
			matrix[i] = new int[vertexNum];
		}
		for (i = 0; i < vertexNum; i++) {
			for (j = 0; j < vertexNum; j++)
				matrix[i][j] = 0;
		}
	}
	~AdjGraph() {
		for (int i = 0; i < vertexNum; i++)
			delete[]matrix[i];
		delete[] matrix;
	}
	Edge FirstEdge(int oneVertex) {
		Edge tmpEdge;
		tmpEdge.start = oneVertex;
		for (int i = 0; i < vertexNum; i++) {
			if (matrix[oneVertex][i] != 0 && matrix[oneVertex][i] != INFINITY) {
				tmpEdge.end = i;
				tmpEdge.weight = matrix[oneVertex][i];
				break;
			}
		}
		return tmpEdge;
	}
	Edge nextedge(Edge oneEdge) {
		Edge tmpedge;
		tmpedge.start = oneEdge.start;
		for (int i = oneEdge.end + 1; i < vertexNum; i++) {
			if (matrix[oneEdge.start][i] != 0 && matrix[oneEdge.start][i] != INFINITY) {
				tmpedge.end = i;
				tmpedge.weight = matrix[oneEdge.start][i];
				break;
			}
		}
		return tmpedge;
	}
	void setedge(int start,int end ,int weight) {
		if (matrix[start][end] == 0)
			edgeNum++;
		matrix[start][end] = weight;
	}
	void deledge(int start, int end) {
		if (matrix[start][end] != 0)
			edgeNum--;
		matrix[start][end] = 0;
	}
	
};
void DFS(AdjGraph& g, int v) {//递归实现深度优先搜索
	g.Mark[v] = VISITED;
	cout << v + 1 << endl;
	for (Edge e = g.FirstEdge(v); g.IsEdge(e); e = g.nextedge(e))
		if (g.Mark[g.ToVertex(e) == UNVISITED])
			DFS(g, g.ToVertex(e));
}
void DFS2(AdjGraph& g) {//非递归实现深度优先搜索
	int i, v, u;
	stack<int>s;
	for (i = 0; i < g.vertexNum; i++)
		g.Mark[i] = UNVISITED;
	for (int i = 0; i < g.vertexNum; i++) {
		if (g.Mark[i] == UNVISITED) {
			s.push(i);
			cout << i + 1 << endl;
			g.Mark[i] = VISITED;
			while (!s.empty()) {
				v = s.top();
				s.pop();
				for (Edge e = g.FirstEdge(v); g.IsEdge(e); e = g.nextedge(e))
				{
					u = e.end;
					if (g.Mark[u] == UNVISITED) {
						s.push(u);
						e = g.FirstEdge(u);
						cout << u + 1 << endl;
						g.Mark[u] = VISITED;
					}
				}
			}
		}
	}
	cout << endl;
}
void BFS(AdjGraph& g,int v) { //广度优先搜索
	queue<int>q;
	for (int i = 0; i < g.vertexNum; i++)
		g.Mark[i] = UNVISITED;
	g.Mark[v] = VISITED;
	cout << v + 1 << endl;
	q.push(v);
	while (!q.empty()) {
		int tmp = q.front();
		q.pop();
		for (Edge e = g.FirstEdge(tmp); g.IsEdge(e); e = g.nextedge(e)) {
			if (g.Mark[g.ToVertex(e)] == UNVISITED) {
				g.Mark[g.ToVertex(e)] = VISITED;
				cout << g.ToVertex(e) + 1 << endl;
				q.push(g.ToVertex(e));
			}
		}
	}
	cout << endl;
}
int main() {
	int n;
	cout << "输入图所含节点个数" << endl;
	cin >> n;
	AdjGraph ag(n);
	int ca[10][10];
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++) {
			cin >> ca[i][j];
			if (ca[i][j] < INFINITY && ca[i][j]>0) {
				ag.setedge(i, j, ca[i][j]);
			}
		}
	DFS2(ag);
	BFS(ag, 1);
	return 0;
}