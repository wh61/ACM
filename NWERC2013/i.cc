#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>

using namespace std;


const int maxn = 1010;

char s[maxn];

typedef long long LL;

const LL inf = 100000000000000000;

LL check(const string&s, int l, int r) {
	bool flag = true;
	for (int i = l; i <= r; ++i) {
		if (s[i] < '0' || s[i] > '9')
			flag = false;
	}
	if (!flag) return -1;
	if (l < r) {
		if (s[l] == '0') return -1;
	}
	LL tmp = 0;
	for (int i = l; i <= r; ++i) {
		tmp = tmp * 10 + s[i] - '0';
	}
	if (tmp >= 1000000000) return -1;
	return tmp;
}


LL f[maxn][maxn];
LL g[maxn][maxn];

//f max
//g min

int main() {

	freopen("in.txt", "r", stdin);

	string str;
	while (cin >> str) {
		int n = str.size();
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				f[i][j] = -inf;
				g[i][j] = inf;
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				if (j - i > 10) break;
				LL val = check(str, i, j);
				if (val == -1) {
					continue;
				}
				f[i][j] = g[i][j] = val;
			}
		}
		for (int l = n - 1; l >= 0; --l) {
			if (str[l] == '+') {
				for (int r = l + 1; r < n; ++r) {
				//	f[l][r] = max(f[l][r], f[l + 1][r]);
				//	g[l][r] = min(g[l][r], g[l + 1][r]);
					for (int k = l + 1; k < r; ++k) {
						f[l][r] = max(f[l][r], f[l + 1][k] + f[k + 1][r]);
						g[l][r] = min(g[l][r], g[l + 1][k] + g[k + 1][r]);
					}
				}
			} else if (str[l] == '-') {
				for (int r = l + 1; r < n; ++r) {
					f[l][r] = max(f[l][r], -g[l + 1][r]);
					g[l][r] = min(g[l][r], -f[l + 1][r]);
					for (int k = l + 1; k < r; ++k) {
						f[l][r] = max(f[l][r], f[l + 1][k] - g[k + 1][r]);
						g[l][r] = min(g[l][r], g[l + 1][k] - f[k + 1][r]);
					}
				}
			}
		}
		cout << g[0][n - 1] << ' ' << f[0][n - 1] << endl;
		//printf("%lld %lld\n", g[0][n - 1], f[0][n - 1]);
	}
	return 0;
}
