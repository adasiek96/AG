#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>

using namespace std;

#define fst first
#define snd second
#define MAX 200
#define PB push_back

int n, m;

// tablica z minimaln¹ iloœci¹ lusterek by dostaæ siê z danego
// punktu do koñca (chyba ostatecznie nawet jej nie u¿ywam,
// tylko testowa³em na niej)
int T[MAX][MAX];

// stany odwiedzenia
bool S[MAX][MAX];

// plansza
char C[MAX][MAX];

// tablica strza³ek ze œcie¿kami takimi, ¿e s¹ one najkrótsze
// ze wzglêdu na liczbê koniecznych lusterek po drodze
char CC[MAX][MAX];

// pole pocz¹tkowe, koñcowe
pair <int, int> start, stop;

//funkcje pomocnicze s¹ opisane szczegó³owo poni¿ej vv
void laser();
void licz(int, int, int);
void dfs(int, int, char, int);
bool pole(int, int);
pair<int, int> strona(char);
bool war(int, int, int);

void lustra();
pair<int, int> update(int, int);
void update2(char, char, int, int);


int main()
{
	int t;
	scanf("%d\n", &t);
	for (int z = 0; z < t; z++) {
		scanf("%d %d\n", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				//scanf("%c", &C[i][j]);
				cin >> C[i][j];
				CC[i][j] = C[i][j];
				S[i][j] = 0;
			}
			//scanf("\n");
		}
		printf("\n");
		laser();
		lustra();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				printf("%c", C[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	system("Pause");
	return 0;
}

// funkcja, która dla ka¿dego pola, wyznacza strza³ki, które mówi¹ jak i gdzie iœæ,
// by do dowolnego pola dotrzeæ z najmniejszê liczb¹ lusterek (jest to podobne
// do wyznaczenia dla ka¿dego pola minimalnej liczby lusterek potrzebnej,
// by dostaæ siê do danego pola)
void laser()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (C[i][j] == '#') T[i][j] = -1;
			else if (C[i][j] == '.') T[i][j] = -2;
			else if (C[i][j] == 'C') { T[i][j] = 0; stop = make_pair(i, j); }
			else { T[i][j] = 0; start = make_pair(i, j); }
		}
	int l = 0;
	licz(start.fst, start.snd, l);

	return;
}

// odpalam dfs-a
void licz(int i, int j, int l)
{
	char f = C[i][j];
	i = i - strona(f).fst;
	j = j - strona(f).snd;

	if (war(i, j, l)) dfs(i, j, f, l);

	return;
}

// sprawdzam, czy nie wyszed³em poza zakres planszy
bool pole(int i, int j)
{
	if (i >= 0 && i < n && j >= 0 && j < m) return true;
	else return false;
}

// zamieniam znaki ^, >, <, v na parê mówi¹c¹, co ten znak robi (+/-)
pair<int, int> strona(char a)
{
	switch (a) {
	case '^': return make_pair(1, 0);
	case '>': return make_pair(0, -1);
	case '<': return make_pair(0, 1);
	case 'v': return make_pair(-1, 0);
	}
}

// dfs, który najpierw idzie po prostej, a na kierunki boczne zwiêksza
// mu siê l, czyli minimalna liczba ruchów, by dostaæ siê do danego pola,
// bo przecie¿ na boki skrêca, wiêc siê zwiêksza ona co jeden (dodajemu
// lusterko), a po prostej zostaje ona bez zmian
void dfs(int i, int j, char c, int l)
{
	
		S[i][j] = true;
		T[i][j] = l;
		CC[i][j] = c;
		if (war(i - strona(c).fst, j - strona(c).snd, l)) dfs(i - strona(c).fst, j - strona(c).snd, c, l);

		if (c == '^' || c == 'v') {
			if (war(i, j - 1, l + 1)) dfs(i, j - 1, '<', l + 1);
			if (war(i, j + 1, l + 1)) dfs(i, j + 1, '>', l + 1);
		}
		else {
			if (war(i + 1, j, l + 1)) dfs(i + 1, j, 'v', l + 1);
			if (war(i - 1, j, l + 1)) dfs(i - 1, j, '^', l + 1);
		}
	

	return;
}

// sprawdzam warunek: czy pole nie jest poza plansz¹, czy jeszcze go nie odwiedzi³em
// (lub jeœli odwiedzi³em to mogê odwiedziæ ponownie tylko wtedy jeœli byæ mo¿e poprawi
// to wynik - dostanê siê na dane pole przy mniejszej liczbie lusterek), czy dane pole jest polem,
// na które mogê wejœæ (czy nie jest zablokowane)
bool war(int i, int j, int l)
{
	if (pole(i, j) && (S[i][j] == false || T[i][j] > l) && (C[i][j] == '.' || C[i][j] == 'C')) return true;
	else return false;
}

// ustawia lusterka na w³aœciwych miejscach, idê od koñca, korzystam z utworzonej
// tablicy CC ze strza³kami i idê po tych strza³kach (przeciwnie do ich kierunku, gdy¿
// one sz³y od pocz¹tku do koñca) czyli tak jakby wracam siê po nich bo one tworzy³y
// "najkrótsz¹" drogê do pola koñcowego
void lustra()
{
	int i = stop.fst, j = stop.snd, i1, j1;
	while (i != start.fst || j != start.snd) {
		i1 = update(i, j).fst;
		j1 = update(i, j).snd;
		if (CC[i][j] != CC[i1][j1]) {
			update2(CC[i][j], CC[i1][j1], i1, j1);
		}
		i = i1;
		j = j1;
	}
	return;
}

// cofanie siê po strza³kach
pair<int, int> update(int i, int j)
{
	if (CC[i][j] == '^') return make_pair(i + 1, j);
	else if (CC[i][j] == '<') return make_pair(i, j + 1);
	else if (CC[i][j] == '>') return make_pair(i, j - 1);
	else return make_pair(i - 1, j);
}

// ustawianie w odpowiednie miejsca podczas cofania lusterek
// u³o¿onych we w³aœciwej pozycji
void update2(char d1, char d2, int i1, int j1)
{
	if (d1 == '^' && d2 == '<') C[i1][j1] = '\\';
	else if (d1 == '^' && d2 == '>') C[i1][j1] = '/';
	else if (d1 == 'v' && d2 == '<') C[i1][j1] = '/';
	else if (d1 == 'v' && d2 == '>') C[i1][j1] = '\\';
	else if (d1 == '<' && d2 == '^') C[i1][j1] = '\\';
	else if (d1 == '<' && d2 == 'v') C[i1][j1] = '/';
	else if (d1 == '>' && d2 == '^') C[i1][j1] = '/';
	else if (d1 == '>' && d2 == 'v') C[i1][j1] = '\\';
	return;
}