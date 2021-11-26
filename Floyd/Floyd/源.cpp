#include <iostream>
#include <stack>
#define MAX_VALUE 1000
#define MAX_VERTEX_COUNT 20 
using namespace std;
struct MGraph
{
	int* edges[MAX_VALUE];
	int iVertexCount, iEdageCount;
};
void ReadDate(MGraph* mGraph);
void Floyd(MGraph* mGraph, int* iArrPath[MAX_VALUE]);
void PrintResult(MGraph* mGraph, int* iArrPath[MAX_VALUE]);

int main()
{
	int* iArrPath[MAX_VALUE];
	for (int i = 0; i < MAX_VALUE; i++) {
		iArrPath[i] = new int[MAX_VALUE];
	}
	MGraph mGraph;
	for (int i = 0; i < MAX_VALUE; i++) {
		mGraph.edges[i] = new int[MAX_VALUE];
	}
	ReadDate(&mGraph);
	Floyd(&mGraph, iArrPath);
	PrintResult(&mGraph, iArrPath);
	system("pause");
	return 0;
}

void ReadDate(MGraph* mGraph) {

	cout << "请输入顶点数和边数" << endl;
	cin >> mGraph->iVertexCount >> mGraph->iEdageCount;
	for (int iRow = 1; iRow <= mGraph->iVertexCount; iRow++) {
		for (int iCol = 1; iCol <= mGraph->iVertexCount; iCol++) {
			mGraph->edges[iRow][iCol] = MAX_VALUE;
		}
	}
	cout << "请输入邻接边及权重" << endl;
	int iRow, iCol, iWeight;
	for (int i = 1; i <= mGraph->iEdageCount; i++) {
		cin >> iRow >> iCol >> iWeight;
		mGraph->edges[iRow][iCol] = iWeight;
	}
}

void Floyd(MGraph* mGraph, int** iArrPath) {

	for (int i = 1; i <= mGraph->iVertexCount; i++) {
		for (int j = 1; j <= mGraph->iVertexCount; j++) {
			iArrPath[i][j] = i;
		}
	}//初始化路径表

	for (int k = 1; k <= mGraph->iVertexCount; k++) {
		for (int i = 1; i <= mGraph->iVertexCount; i++) {
			for (int j = 1; j <= mGraph->iVertexCount; j++) {
				if (mGraph->edges[i][k] + mGraph->edges[k][j] < mGraph->edges[i][j]) {
					mGraph->edges[i][j] = mGraph->edges[i][k] + mGraph->edges[k][j];
					iArrPath[i][j] = iArrPath[k][j];
				}
			}
		}
	}

}

void PrintResult(MGraph* mGraph, int** iArrPath) {

	cout << "起点 -> 终点   距离   路径" << endl;

	for (int i = 1; i <= mGraph->iVertexCount; i++) {
		for (int j = 1; j <= mGraph->iVertexCount; j++) {
			if (i != j) {
				cout << i << "->" << j << "\t\t";
				if (mGraph->edges[i][j] == MAX_VALUE) {
					cout << "无连通路径" << "\t\t" << endl;
				}
				else {
					cout << mGraph->edges[i][j] << "\t\t";
					std::stack<int> stackVertices;
					int k = j;
					do
					{
						k = iArrPath[i][k];
						stackVertices.push(k);
					} while (k != i);

					cout << stackVertices.top();
					stackVertices.pop();

					unsigned int nLength = stackVertices.size();
					for (unsigned int nIndex = 0; nIndex < nLength; nIndex++)
					{
						cout << " -> " << stackVertices.top();
						stackVertices.pop();
					}
					cout << " -> " << j << endl;
				}
			}
		}
	}
}