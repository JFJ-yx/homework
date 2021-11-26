#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXNUM 9

int graph[MAXNUM][MAXNUM];
int D[MAXNUM];
int final[MAXNUM];
int V0;


void createGraph(int V1, int V2, int weight)//V1->V2
{
    graph[V1][V2] = weight;
}

void inputGraph()
{
    char ch;
    int V1, V2, weight;
    do
    {
        cin >> ch;
        if (ch != '#')
            V1 = ch - '0';
        else break;
        cin >> V2;
        cin >> weight;
        createGraph(V1, V2, weight);
    } while (1);
}

int shortestPath(int Vj)
{
    int i;
    int temp = 999;
    for (i = 0; i < MAXNUM; i++)
    {
        if ((graph[i][Vj] > 0) && (graph[i][Vj] + D[i] < temp))
            temp = graph[i][Vj] + D[i];
    }
    if (temp != 999) D[Vj] = temp;
    return temp;
}

void Dijkstra()
{
    int i, j, k, Va, Vb, temp;
    D[V0] = 0;
    final[V0] = 1;
    for (i = 0; i < MAXNUM; i++)
    {
        if (i != V0)
        {
            if (graph[V0][i] > 0)
                D[i] = graph[V0][i];
            else
                D[i] = 999;
        }

    }

    for (i = 1; i < MAXNUM; i++) 
    {
        temp = 999;
        for (j = 0; j < MAXNUM; j++)
        {
            if (1 == final[j])
            {
                for (k = 0; k < MAXNUM; k++)
                {
                    if ((graph[j][k] > 0) && (0 == final[k]) && (graph[j][k] < temp))
                    {
                        temp = graph[j][k];
                        Va = j;
                        Vb = k;
                    }
                }
            }
        }

        if (temp != 999)
        {
            final[Vb] = 1;
            D[Vb] = temp;
        }
        
        for (j = 0; j < MAXNUM; j++)
        {
            if (1 == final[j])
            {
                shortestPath(j);
            }
        }
    }

}

void display()
{
    int i;
    cout <<"从"<<V0<<"出发，到达个点的最小路径为:"<<endl;
        for (i = 0; i < MAXNUM; i++)
        {
            if (D[i] != 999)
                cout << i << ":" << D[i] << endl;
        }
}

int main()
{

    cout << "输入各边的权值，以#结束" << endl;
    inputGraph();
    cout << "请输入原点"<<endl;
        cin >> V0;
    Dijkstra();
    display();

    return 0;
}