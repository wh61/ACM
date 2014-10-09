#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>


using namespace std;

long double dp[11111][55];
long double f[11111][55];

int st[55], nx[11111], ve[11111];

inline void add(int i, int a, int b) {
	ve[i] = b;
	nx[i] = st[a];
	st[a] = i;
}

int tot = 0;

int de[55];


int main() {

	freopen("in.txt", "r", stdin);


	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m, d;
		scanf("%d%d%d", &n, &m, &d);
		memset(de, 0, sizeof(de));
		memset(st, 0, sizeof(st));
		int tot = 0;
		for (int i = 0; i < m; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			de[x]++;
			de[y]++;
			add(++tot, x, y);
			add(++tot, y, x);
		}



		double ans[55];


		for (int V = 1; V <= n; ++V) {


		for (int i = 0; i <= d; ++i) for (int j = 1; j <= n; ++j) dp[i][j] = 0;
		for (int v = 1; v <= n; ++v) dp[0][v] = 1.0 / n;

		for (int k = 1; k <= d; ++k) {
			for (int v = 1; v <= n; ++v) {
				dp[k][v] = 0;
				for (int i = st[v]; i; i = nx[i]) if (ve[i] != V){
					dp[k][v] += dp[k - 1][ve[i]] / de[ve[i]];
				}
			}
		}

		long double tmp = 0;
		for (int k = 0; k <= d; ++k)
			tmp += dp[k][V];
		ans[V] = 1 - tmp;

		}




		for (int i = 1; i <= n; ++i) ans[i] = 1 - f[0][i];




		for (int v = 1; v <= n; ++v) {
			printf("%.8lf\n", ans[v]);
		}


	}
	return 0;
}
