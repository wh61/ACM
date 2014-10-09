#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long LL;

LL t[3][3];
LL dp[44][3][3];


int main() {

	freopen("in.txt", "r", stdin);

	memset(t, 0, sizeof(t));
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cin >> t[i][j];
		}
	}
	int n;
	cin >> n;
	memset(dp, 0, sizeof(dp));
	for (int k = 1; k <= n; ++k) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (i == j) continue;
				int tmp = 0;
				for (int k = 0; k < 3; ++k) if (i != k && j != k) tmp = k;
				LL tmp1 = dp[k - 1][i][tmp] + t[i][j] + dp[k - 1][tmp][j];
				LL tmp2 = dp[k - 1][i][j] + t[i][tmp] + t[tmp][j] + dp[k - 1][j][i] + dp[k - 1][i][j];
				dp[k][i][j] = min(tmp1, tmp2);
			}
		}
		for (int h = 0; h < 3; ++h) {
			for (int i = 0; i < 3; ++i) if (i != h) {
				for (int j = 0; j < 3; ++j) {
					if (i != j && h != j)
						dp[k][i][j] = min(dp[k][i][j], dp[k][i][h] + dp[k][h][j]);
				}
			}
		}
	}
	cout << dp[n][0][2] << endl;

	return 0;
}
