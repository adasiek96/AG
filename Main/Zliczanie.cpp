#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAX (int)1e6

using namespace std;

int n, t[10], a[MAX], b[MAX], w[MAX];

void wczytaj() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d %d", &a[i], &b[i]);
}

void zlicz() {
	for (int i = 0; i < n; i++) t[b[i] - 1]++;
}

void oblicz_indeksy() {
	for (int i = 1; i < 10; i++) t[i] += t[i - 1];
	for (int i = 0; i < 10; i++) t[i]--;
}

void posortuj_wszystko() {
	for (int i = n - 1; i >= 0; i--) {
		w[t[b[i] - 1]] = a[i];
		t[b[i] - 1]--;
	}
}

void wyswietl() {
	for (int i = 0; i < n; i++)
		printf("%d\n", w[i]);
}

int main() {

	wczytaj();
	zlicz();
	oblicz_indeksy();
	posortuj_wszystko();
	wyswietl();


	system("Pause");
	return 0;
}