#include <cstdlib>
#include <cstdio>
#include <algorithm>

#define MAX_n (int)2e2
#define MAX_k (int)2e4 + 1

using namespace std;

int n, k, B[MAX_n], C[MAX_n];
struct bank {
	int m, tab[MAX_n];
};
bank T[MAX_k];

void plecak()
{
	for (int i = 1; i <= k; i++) {
		int kw = k, j = 0, mini = MAX_k, idx = 0;
		T[i].m = mini;
		while (j < n) {
			// czy nomina³ siê mieœci
			if (B[j] <= i) {
				// czy mam jeszcze ten nomina³
				if (C[j] - T[i - B[j]].tab[j] != 0) {
					// czy warto go u¿yæ
					if (T[i - B[j]].m < mini) {
						mini = T[i - B[j]].m;
						T[i].m = mini + 1;
						//cout << T[i].m << endl;
						memcpy(T[i].tab, T[i - B[j]].tab, MAX_n * 4);
						T[i].tab[j] = T[i - B[j]].tab[j] + 1;
					}
				}
			}
			j++;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &B[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &C[i]);
	scanf("%d", &k);

	plecak();

	printf("%d\n", T[k].m);
	for (int i = 0; i < n; i++) {
		printf("%d", T[k].tab[i]);
		if (i != n - 1) printf(" ");
		else printf("\n");
	}
	

	system("Pause");
	return 0;
}

