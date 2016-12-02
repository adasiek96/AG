#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#define MAX 101

using namespace std;

string T[MAX];
int n, licznik;

//CR OK
int HASH(string key) {
	int h = 0;
	for (int i = 0; i < key.length(); i++) {
		h += (i + 1) * (int)key[i];
	}
	h *= 19;
	h = h % 101;
	return h;
}

//CR OK
void ADD(string key) {
	int j = 0, p;
	while (j < 20) {
		p = HASH(key) + j * j + 23 * j;
		p = p % 101;
		if (T[p] == key) return;
		else if (T[p] != "") j++;
		else {
			T[p] = key;
			licznik++;
			break;
		}
	}
}


//CR OK
void DEL(string key) {
	int j = 0, p;
	while (j < 20) {
		p = HASH(key) + j * j + 23 * j;
		p = p % 101;
		if (T[p] == key) {
			T[p] = "";
			licznik--;
			return;
		}
		j++;
	}
}

void DO() {
	string s, key;
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		cin >> s;
		key = "";
		for (int i = 4; i < s.length(); i++)
			key += s[i];
		if (s[0] == 'A') ADD(key);
		else if (s[0] == 'D') DEL(key);
	}
	printf("%d\n", licznik);
	for (int i = 0; i < MAX; i++) {
		if (T[i] != "") {
			printf("%d", i);
			printf("%c", ':');
			cout << T[i] << endl;
		}
	}
}

int main() {
	int x;
	scanf("%d", &x);
	while (x != 0) {
		DO();
		x--;
		if (x != 0)
			for (int i = 0; i < MAX; i++) {
				T[i] = "";
				licznik = 0;
			}
	}

	system("Pause");
	return 0;
}