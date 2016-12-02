#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct trzy {
	int a, x, b;
};

string s;
char S[(int)1e6];
int n, m, M = 1, L[(int)1e5], R[(int)1e5];
trzy D[(int)21e5];

void find_M()
{
	int N = n;
	while (N != 0) {
		M *= 2;
		N /= 2;
	}
	M--;
}

trzy sum(trzy tr1, trzy tr2)
{
	trzy tr;
	int t = min(tr1.a, tr2.b);
	tr.a = tr1.a + tr2.a - t;
	tr.x = tr1.x + tr2.x + 2 * t;
	tr.b = tr1.b + tr2.b - t;
	return tr;
}

void update()
{
	for (int i = M; i < M + n; i++) {
		trzy tr;
		if (S[i - M] == '(') {
			tr.a = 1;
			tr.x = 0;
			tr.b = 0;
		}
		else {
			tr.a = 0;
			tr.x = 0;
			tr.b = 1;
		}
		D[i] = tr;
	}
	for (int i = M - 1; i >= 0; i--) {
		D[i] = sum(D[2 * i + 1], D[2 * i + 2]);
	}
}

trzy F1(int a, int b, int x, int y, int w)
{
	trzy tr;
	if (a > y || b < x || x > y) {
		tr.a = 0;
		tr.x = 0;
		tr.b = 0;
		return tr;
	}
	if (a == x && b == y) return D[w];
	int s = (x + y) / 2;
	return sum(F1(a, min(b, s), x, s, 2 * w + 1), F1(max(a, s + 1), b, s + 1, y, 2 * w + 2));
}

int main()
{
	cin >> s;
	n = s.length();
	for (int i = 0; i < n; i++)
		S[i] = s[i];
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> L[i] >> R[i];
		L[i]--;
		R[i]--;
	}

	find_M();
	update();

	for (int i = 0; i < m; i++)
		printf("%d\n", F1(L[i], R[i], 0, M, 0).x);

	system("Pause");
	return 0;
}