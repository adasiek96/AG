#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int n, a[(int)1e5];

int main()
{
	int wynik = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);

	sort(a, a + n);

	for (int i = 0; i < n; i++) wynik += a[i];
	for (int i = 0; i < n / 2; i++) {
		wynik += a[n - 1 - i] - a[i];
	}

	printf("%d\n", wynik);

	system("Pause");
	return 0;
}