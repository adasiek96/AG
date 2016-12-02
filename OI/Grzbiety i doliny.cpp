#include <iostream>
#include <cstdio>
#include <utility>
#include <cstdlib>
#include <queue>

using namespace std;

// deklaracja tablic i kolejki
int wysokosci[1001][1001];
bool odwiedzenia[1001][1001];
queue < pair<int, int> > kolejka;

// funkcje pomocnicze
bool zakres(int, int, int);
int sprawdz(int, int, int, queue <pair <int, int> >*, bool);
int grzbiety(int, int, int, bool);


int main()
{
	// deklaracja zmiennych
	int n, licz_dol = 0, licz_grz = 0;

	// wczytanie danych
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			odwiedzenia[i][j] = false;
			scanf("%d", &wysokosci[i][j]);
		}

	// wyszukiwanie dolin
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			licz_dol += grzbiety(i, j, n, true);
		}

	// wyszukiwanie grzbietów
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			odwiedzenia[i][j] = false;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			licz_grz += grzbiety(i, j, n, false);
		}

	// wypisanie danych
	printf("%d %d\n", licz_grz, licz_dol);

	system("Pause");
	return 0;
}

bool zakres(int x, int y, int n)
{
	if (x >= 0 && y >= 0 && x < n && y < n) return true;
	else return false;
}

int sprawdz(int x, int y, int war, queue <pair <int, int> >* kolejka, bool b)
{
	if (b) { if (wysokosci[x][y] < war) return 0; }
	else { if (wysokosci[x][y] > war) return 0; }
	if (wysokosci[x][y] == war && odwiedzenia[x][y] == false) {
		(*kolejka).push(make_pair(x, y));
		odwiedzenia[x][y] = true;
	}
	return 1;
}

int grzbiety(int x, int y, int n, bool b)
{
	if (odwiedzenia[x][y] == false) {
		odwiedzenia[x][y] = true;
		pair <int, int> para;
		int war = wysokosci[x][y];
		int wyn = 1;
		kolejka.push(make_pair(x, y));
		while (kolejka.empty() == false) {
			para = kolejka.front();
			kolejka.pop();
			x = para.first;
			y = para.second;
			for (int dx = -1; dx <= 1; dx++)
				for (int dy = -1; dy <= 1; dy++)
					if (zakres(x + dx, y + dy, n))
						if (dx != 0 || dy != 0)
							wyn = min(sprawdz(x + dx, y + dy, war, &kolejka, b), wyn);
		}
		return wyn;
	}
	else return 0;
}