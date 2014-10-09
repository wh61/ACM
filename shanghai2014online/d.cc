#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxm = 1111;
const int maxn = 12;

double p[maxn][maxn];
double a[maxn][maxm];

double dp[maxn][1 << maxn];

double get(int n, int m) {
	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j < 1 << n; ++j) {
			dp[i][j] = 0;
		}
	}
	for (int i = 1; i <= m; ++i) {
		for (int mask = 0; mask < 1 << n; mask++) {
			for (int j = 0; j < n; ++j) {
				if (((mask >> j) & 1) == 0) {
					dp[i][mask | (1 << j)] = max(dp[i][mask | (1 << j)], dp[i - 1][mask] + p[j][i - 1]);
				}
			}
		}
	}
	double ans = 0;
	for (int mask = 0; mask < 1 << n; ++mask) {
		ans = max(ans, dp[m][mask]);
	}
	return ans;
}


int main() {


	freopen("in.txt", "r", stdin);

	int T, n, m, ca = 0;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> a[i][j];
			}
		}
		double ans = 0;
		for (int k = 0; k <= m / n; ++k) {
			int L = k * n, R = min(k * n + n, m);
			for (int i = 0; i < n; ++i) {
				for (int j = L; j < R; ++j) {
					p[i][j - L] = a[i][j];
				}
			}
			ans += get(n, R - L);
		}
		printf("Case #%d: %.5lf\n", ++ca, ans);
	}

	return 0;
}
