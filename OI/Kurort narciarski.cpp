#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <queue>
#include <vector>

#define MAX_P 1000
#define MAX_H 2000

#define PB push_back
#define FOR(II, NN) for(int (II) = 0; (II) < (NN); (II)++)
#define fst first
#define snd second

using namespace std;

int n, np, k, m, p1, p2, q1, q2, r, b, s, minimum;
vector< pair<int, int> > S[MAX_P];
bool stany[MAX_P][MAX_H + 1];
queue <pair <int, int> > Q; // polana, hajs

int bfs();

int main()
{
	scanf("%d%d%d", &n, &np, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d%d", &p1, &p2);
		p1--;
		p2--;
		S[p1].PB(make_pair(p2, 0));
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &q1, &q2, &r);
		q1--;
		q2--;
		S[q1].PB(make_pair(q2, r));
	}

	scanf("%d%d", &b, &s);
	b--;

	int wynik = bfs();

	printf("%d\n", wynik);

	system("Pause");
	return 0;
}

void wrzucam(int a, int z)
{
	if (a < np) minimum = min(minimum, z);
	Q.push(make_pair(a, z));
	stany[a][z] = 1;
}

int bfs()
{
	int x, y, z, a;
	minimum = s;
	Q.push(make_pair(b, s));
	while (Q.empty() == false) {
		x = Q.front().fst;
		y = Q.front().snd;
		Q.pop();
		if (minimum == 0) return 0;

		for (int i = 0; i < S[x].size(); i++)
		{
			pair<int, int> p = S[x][i];
			a = p.fst;
			z = y - p.snd;

			if (z >= 0 && stany[a][z] == 0)
				wrzucam(a, z);
		}
	}
	return minimum;
}