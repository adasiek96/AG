#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>

#define MAX (int)1e4

using namespace std;

int n, m, w1, w2;
bool B[MAX], BB[MAX];
vector<int> D1[MAX], D2[MAX];
stack<int> S;
vector<int> v;
vector< vector<int> > V;
int T[MAX];
int kolor = 1;

void wczytaj() {
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		if (a != b) {
			D1[a - 1].push_back(b - 1);
			D2[b - 1].push_back(a - 1);
		}
	}
}

int znajdz_pierwszy(vector<int> D[MAX]) {
	for (int i = 0; i < MAX; i++)
		if (!BB[i] && D[i].size() != 0) return i;
	return -1;
}

void dfs1(int j) {
	BB[j] = true;
	for (int i = 0; i < D1[j].size(); i++)
		if (!BB[D1[j][i]]) {
			dfs1(D1[j][i]);
		}
	S.push(j);
}

void dfs2(int j, int kolor) {
	if (!BB[j] || B[j]) return;
	B[j] = true;
	v.push_back(j);
	T[j] = kolor;
	for (int i = 0; i < D2[j].size(); i++)
		dfs2(D2[j][i], kolor);
}

bool brak_koncow(vector<int> v, vector<int> D[MAX]) {
	int licznik = 0;
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < D[v[i]].size(); j++)
			if (T[D[v[i]][j]] != T[v[i]])
				return false;
	return true;
}

int main() {

	wczytaj();

	for (int j = 0; j < n; j++)
	{
		if (BB[j]) continue;
		BB[j] = true;

		dfs1(j);

		for (int i = 0; i < MAX; i++) B[i] = false;
		while (S.size() != 0) {
			int k = S.top();
			S.pop();
			if (!B[k]) {
				dfs2(k, kolor);
				V.push_back(v);
				v.clear();
				kolor++;
			}
		}
	}

	if (V.size() == 1) {
		w1 = 0;
		w2 = 0;
	}
	else {
		for (int i = 0; i < V.size(); i++)
			if (brak_koncow(V[i], D1)) w1++;
		for (int i = 0; i < V.size(); i++)
			if (brak_koncow(V[i], D2)) w2++;
	}

	int d = max(w1, w2);

	cout << d << endl;

	system("Pause");
	return 0;
}