#include <cstdlib>
#include <cstdio>

#define MAX 200

using namespace std;

int T[MAX][MAX], n;
bool B[MAX][MAX];

void FLOYD_WARSHALL() {
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (T[i][j] == T[i][k] + T[k][j] && k != i && k != j) {
					B[i][j] = false;
					B[j][i] = false;
				}
				else if (i == j) B[i][j] = false; 
			}

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if (B[i][j]) printf("%d %d\n", i + 1, j + 1);
}

void DO() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			scanf("%d", &T[i][j]);
			B[i][j] = true;
		}
	FLOYD_WARSHALL();
	printf("\n");
}

int main() {
	int t;
	scanf("%d", &t);
	while (t > 0) {
		DO();
		t--;
	}

	system("Pause");
	return 0;
}