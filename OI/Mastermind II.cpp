#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#define MAX 9

int u, T1[10];
bool O1[10];

struct uklad {
	int A, B, tab[MAX];
};
uklad U[MAX];

struct tablica {
	int t[10];
};
vector<tablica> P;

void dfs(bool O[10], int T[10], int k)
{
	for (int i = 1; i <= 9; i++) {
		if (!O[i]) {
			tablica T2;
			bool O2[10];
			memcpy(O2, O, 10);
			memcpy(T2.t, T, 40);
			O2[i] = true;
			T2.t[k] = i;
			if (k == u - 1) P.push_back(T2);
			else dfs(O2, T2.t, k + 1);
		}
	}
}

bool sprawdz(int T01[10], int T02[10], int A, int B)
{
	int A1 = 0, B1 = 0, S[10];
	for (int i = 0; i <= 9; i++)
		S[i] = 0;

	for (int i = 0; i < u; i++) {
		if (T01[i] == T02[i]) A1 += T01[i];
		S[T01[i]]++;
		S[T02[i]]++;
	}

	for (int i = 0; i < 10; i++)
		if (S[i] == 2) {
			B1 += i;
		}
	
	B1 -= A1;

	if (A1 == A && B1 == B) return true;
	else return false;
}

void sprawdz_all()
{
	int licznik = 0;
	for (int i = 0; i < P.size(); i++) {
		for (int j = 0; j < u; j++) {
			if (!sprawdz(P[i].t, U[j].tab, U[j].A, U[j].B)) break;
			else licznik++;
		}
		if (licznik == u) {
			for (int k = 0; k < u; k++) {
				cout << P[i].t[k];
				if (k != u - 1) cout << " ";
				else cout << endl;
			}
			return;
		}
		licznik = 0;
	}
}

void rozwal_zadanko()
{
	dfs(O1, T1, 0);
	sprawdz_all();
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin >> u;
	for (int i = 0; i < u; i++) {
		cin >> U[i].A >> U[i].B;
		for (int j = 0; j < u; j++)
			cin >> U[i].tab[j];
	}

	rozwal_zadanko();

	system("Pause");
	return 0;
}