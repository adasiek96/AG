#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>

#define MAX (int)1e6

using namespace std;

int N, P[MAX], D[MAX], p, d, S[MAX], s;
bool B[MAX];

void wczytaj() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &P[i], &D[i]);
		p += P[i];
		d += D[i];
	}
}

bool czy_istnieje_stacja_wypadowa() {
	if (p < d) {
		for (int i = 0; i < N; i++) B[i] = false;
		return false;
	}
	return true;
}

void wyswietl() {
	for (int i = 0; i < N; i++)
		if (B[i]) printf("TAK\n");
		else printf("NIE\n");
}

void znajdz_stacje_wypadowe(bool b) {
	if (!b) {
		for (int i = 0; i < N / 2; i++) {
			swap(P[i], P[N - 1 - i]);
			swap(D[i], D[N - 1 - i]);
		}
		for (int i = 1; i < N; i++) {
			swap(D[i - 1], D[i]);
		}
	}
	S[0] = 0;
	for (int i = 1; i < N; i++) S[i] = S[i - 1] + P[i - 1] - D[i - 1];
	int m = INT_MAX, k = -1;
	for (int i = 0; i < N; i++) if (S[i] < m) {
		m = S[i];
		k = i;
	}
	if (m <= 0) {
		if (!b) B[N - 1 - k] = true;
		else B[k] = true;
	}
	int i = k - 1;
	if (i == -1) i += N;
	while (i != k) {
		s += P[i] - D[i];
		if (s >= 0) {
			if (!b) B[N - 1 - i] = true;
			else B[i] = true;
			s = 0;
		}
		i--;
		if (i == -1) i += N;
	}
	s = 0;
}


int main() {

	wczytaj();

	if (czy_istnieje_stacja_wypadowa()) {
		znajdz_stacje_wypadowe(true);
		znajdz_stacje_wypadowe(false);
	}

	wyswietl();

	system("Pause");
	return 0;
}