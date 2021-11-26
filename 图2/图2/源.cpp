#include<iostream>
#include<queue>
using namespace std;
class Edge
{
public:
    int jp;// 邻接点域(边连接下标)
    Edge* next;
    Edge()
    {
        jp = 0;
        next = NULL;
    }
};
class Node
{
public:
    int x;//顶点数字
    Edge* bian;//顶点指向的第一条边 
    Node(int a)
    {
        x = a;
        bian = NULL;
    }
    Node()
    {
        x = 0;
        bian = NULL;
    }
};
const int MaxSize = 10;
int visited[MaxSize] = { 0 };//vis数组 
class Gat//邻接表
{
public:
    Gat(int a[], int n, int e)
    {
        int temp;
        num = n;
        this->num1 = e;
        for (int i = 0; i < num; i++)
        {
            node[i].x = a[i];
        }
        for (int k = 0; k < num1; k++)
        {
            int i, j, mp;
            cin >> i >> j;
            Edge* s = new Edge;
            s->jp = j;
            s->next = node[i].bian;
            node[i].bian = s;
        }
        for (int p = 0; p < n; p++)
        {
            Edge* wap;
            Edge* wasp = node[p].bian;
            for (; wasp != NULL; wasp = wasp->next)
            {
                for (wap = wasp->next; wap != NULL; wap = wap->next)
                {
                    if (wasp->jp > wap->jp)
                    {
                        temp = wasp->jp;
                        wasp->jp = wap->jp;
                        wap->jp = temp;
                    }
                }
            }
        }
    }
    void DFS(int v)
    {
        cout << node[v].x << " ";
        visited[v] = 1;
        Edge* p = node[v].bian;
        while (p != NULL)
        {
            int j = p->jp;
            if (visited[j] == 0)
                DFS(j);
            p = p->next;
        }
    }
    void BFS()
    {
        int jm = 1;
        int BFSvisited[10] = { 0 };
        queue<int>sap;
        sap.push(0);
        for (int i = 0; i < this->num; i++)
        {
            Edge* ss = node[i].bian;
            for (; jm > 0; jm--)
            {
                if (BFSvisited[sap.front()] == 0)
                    cout << node[sap.front()].x << " ";
                BFSvisited[sap.front()] = 1;
                sap.pop();
            }
            while (ss)
            {
                sap.push(ss->jp);
                jm++;
                ss = ss->next;
            }
        }

    }
    void cout0()
    {
        for (int i = 0; i < num; i++)
        {
            cout << node[i].x;
            Edge* sap = node[i].bian;
            for (; sap != NULL; sap = sap->next)
            {
                cout << "->" << node[sap->jp].x;
            }
            cout << endl;
        }
    }
    Node node[MaxSize];// 存放顶点的数组
    int num, num1;//顶点个数，边数 
};
int main()
{
    int arry[] = { 0,1,2,3,4 };
    Gat tu(arry, 5, 12);// 数组值    节点个数   边的个数
    tu.cout0();
    cout << endl;
    tu.BFS();
    cout << endl;
    tu.DFS(0);
}