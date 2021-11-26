#include<iostream>
#include"minheap.cpp"
using namespace std;

class UfSets {
private:
	int n;
	int* root;
	int* next;
	int* length;
public:
	UfSets(int size) {
		n = size;
		for (int i = 0; i < n; i++) {
			root[i] = next[i] = i;
			length[i] = 1;
		}
	}
	int find(int v) {
		return root[v];
	}
	void Union(int v, int u);
};
void UfSets::Union(int v, int u)
{
	if (root[u] == root[v])
		return;
	else if (length[root[v]] < length[root[u]]) {
		int rt = root[v];
		length[root[u]] += length[rt];
		root[rt] = root[u];
		for (int j = next[rt]; j != rt; j = next[j])
			root[j] = root[u];
		int temp = next[rt];
		next[rt] = next[u];
		next[u] = temp;     //将两个等价类的元素连接起来
	}
	else {
		int rt = root[u];
		length[root[v]] += length[rt];
		root[rt] = root[v];
		for (int j = next[rt]; j != rt; j = next[j])
			root[j] = root[v];
		int temp = next[rt];
		next[rt] = next[v];
		next[v] = temp;
	}
}
