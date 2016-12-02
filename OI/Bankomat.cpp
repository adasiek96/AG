#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>

#define MAX_n (short)1e3
#define MAX_t (short)1e4
#define fst first
#define snd second

using namespace std;

struct para {
	string fst;
	short snd;
};

short n, W, T[MAX_n], O[MAX_t];
vector<short> B[10];
string S[MAX_n];
vector<para> V;

string long2short(string l)
{
	string ret;
	ret += l[0];
	for (int i = 1; i < 4; i++)
		if (ret[ret.size() - 1] != l[i]) ret += l[i];

	return ret;
}

char ASCII(int a)
{
	return (char)(a + 48);
}

void make_B(short t, string slowo)
{
	for (int i = 0; i <= 9; i++)
		B[i].clear();

	for (int j = 0; j <= 9; j++) {
		if (slowo[t - 1] == ASCII(j)) B[j].push_back(t - 1);
		else B[j].push_back(-1);
	}

	for (int i = t - 2; i >= 0; i--)
		for (int j = 0; j <= 9; j++) {
			if (slowo[i] == ASCII(j)) B[j].push_back(i);
			else {
				short qw = B[j].back();
				B[j].push_back(qw);
			}
		}
}

void F()
{
	string str = "";
	vector<pair<string, string> > A;
	for (char a = '0'; a <= '9'; a++)
		for (char b = '0'; b <= '9'; b++)
			for (char c = '0'; c <= '9'; c++)
				for (char d = '0'; d <= '9'; d++) {
					str += a;
					str += b;
					str += c;
					str += d;
					A.push_back(make_pair(long2short(str), str));
					str = "";
				}

	sort(A.begin(), A.end());
	
	short licze = 1;
	for (int i = 1; i < (int)A.size(); i++) {
		if (A[i].fst == A[i - 1].fst) licze++;
		else {
			para pp;
			pp.fst = A[i - 1].fst;
			pp.snd = licze;
			V.push_back(pp);
			licze = 1;
		}
	}
	para pp;
	pp.fst = A[A.size() - 1].fst;
	pp.snd = licze;
	V.push_back(pp);
}

bool czy_B(string str, short idx)
{
	short id = 0;
	if (B[(int)str[0] - 48][T[idx] - 1 - id] == -1) return false;
	for (int i = 0; i < str.length(); i++)
		for (int j = 0; j <= 9; j++) {
			if (str[i] == ASCII(j)) {
				if (B[j][T[idx] - 1 - id] == -1) return false;
				else id = B[j][T[idx] - 1 - id];
				break;
			}
		}
	return true;
}
void czy_all()
{
	for (int i = 0; i < n; i++) {
		make_B(T[i], S[i]);
		for (int j = 0; j < V.size(); j++) {
			if (O[j] == 0 && !czy_B(V[j].fst, i))
				O[j] = 1;
		}
	}

	for (int i = 0; i < V.size(); i++)
		if (O[i] == 0)
			W += V[i].snd;

	return;
}

void rozwale_w_koncu_to_zadanie_za_jednym_razem_na_100_punktow()
{
	F();
	czy_all();

	cout << W << endl;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> T[i];
		cin >> S[i];
	}
	

	rozwale_w_koncu_to_zadanie_za_jednym_razem_na_100_punktow();


	system("Pause");
	return 0;
}