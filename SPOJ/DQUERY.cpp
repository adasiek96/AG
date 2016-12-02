#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

#define MAX_2M (int)66e3
#define MAX_Q (int)2e5
#define MAX_a (int)1e6

using namespace std;

struct w {
	int b, t, a, idx; // prawy koniec/pozycja, typ, lewy koniec/wartoœæ, indeks/-1
};

int n, q, m = 1, D[2 * MAX_2M], T[MAX_a], W[MAX_Q];
vector<w> V;

void znajdz_m(int n)
{
	int N = n;
	while (N != 0) {
		m *= 2;
		N /= 2;
	}
	m--;
}

bool sort_w(const w &cztery1, const w &cztery2)
{
	if (cztery1.b != cztery2.b) return cztery1.b < cztery2.b;
	return cztery1.t < cztery2.t;
}

void dodaj(int x)
{
	int id = m + x;
	D[id]++;
	while (id != 0) {
		id = (id - 1) / 2;
		D[id]++;
	}
	D[id]++;
}

void usun(int x)
{
	int id = m + x;
	D[id]--;
	while (id != 0) {
		id = (id - 1) / 2;
		D[id]--;
	}
	D[id]--;
}

int F1(int a, int b, int x, int y, int w)
{
	if (a > y || b < x || x > y) return 0;
	if (a == x && b == y) return D[w];
	int s = (x + y) / 2;
	return F1(a, min(b, s), x, s, 2 * w + 1) + F1(max(a, s + 1), b, s + 1, y, 2 * w + 2);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		w cztery;
		scanf("%d", &cztery.a);
		cztery.b = i;
		cztery.t = 0;
		cztery.idx = -1;
		V.push_back(cztery);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		w cztery;
		scanf("%d%d", &cztery.a, &cztery.b);
		cztery.a--;
		cztery.b--;
		cztery.idx = i;
		cztery.t = 1;
		V.push_back(cztery);
	}
	for (int i = 0; i < MAX_a; i++)
		T[i] = -1;

	sort(V.begin(), V.end(), sort_w);
	znajdz_m(n);

	for (int i = 0; i < V.size(); i++) {
		if (V[i].t == 0)
			if (T[V[i].a] == -1) {
				dodaj(V[i].b);
				T[V[i].a] = V[i].b;
			}
			else {
				usun(T[V[i].a]);
				dodaj(V[i].b);
				T[V[i].a] = V[i].b;
			}
		else W[V[i].idx] = F1(V[i].a, V[i].b, 0, m, 0);
	}

	for (int i = 0; i < q; i++)
		printf("%d\n", W[i]);

	system("Pause");
	return 0;
}