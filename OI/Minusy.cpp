#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAX (int)1e6

using namespace std;

int n;
char c[MAX];

int main() {
	scanf("%d\n", &n);
	for (int i = 0; i < n - 1; i++) {
		scanf(" %c", &c[i]);
	}
	c[n - 1] = '-';
	bool bb = false;
	char a, b;
	int i = 1;
	a = c[0];
	b = c[1];
	while (i != n) {
		// pocz¹tkowy nawias
		if (a == '-' && b == '+' && bb == false) {
			cout << "-(";
			bb = true;
		}
		//przed³u¿anie nawiasu
		else if (a == '+' && b == '+' && bb == true) {
			cout << "-";

		}
		else if (a == '-' && b == '+') {
			cout << "-(";
		}
		else if (a == '+' && b == '-') {
			cout << "-)";
			bb = false;
		}
		else if (a == '-' && b == '-') {
			cout << "-";
		}
		else cout << "?";
		
		a = c[i];
		b = c[i + 1];
		i++;
	}
	if (bb == true) cout << ")";


	system("Pause");
	return 0;
}