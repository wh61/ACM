#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 1555;

typedef unsigned long long LL;

LL dp[maxn][maxn];


int main() {


	freopen("in.txt", "r", stdin);

	int T, ca = 0;
	cin >> T;
	while (T--) {
		int n;
		LL x, y, z, t;
		cin >> n >> x >> y >> z >> t;


		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j)
				dp[i][j] = 0;


		LL ans = x * t * n;

		//dp[i][j] i-ta j-IItypeta
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= i; ++j) {
			    LL tmp1 = t + z * (j - 1);
				tmp1 *= y * (i - j);
				LL tmp2 = t + z * j;
				tmp2 *= y * (i - j - 1);
				if (j > 0 && j < i) {
					dp[i][j] = max(dp[i - 1][j - 1] + tmp1, dp[i - 1][j] + tmp2);
				} else if (j == 0) {
					dp[i][j] = dp[i - 1][j] + tmp2;
				} else if (j == i) {
					dp[i][j] = dp[i - 1][j - 1] + tmp1;
				}
				LL tmp = 0;
				tmp += (x + (i - j) * y) * (n - i) * (t + z * j);
				ans = max(ans, dp[i][j] + tmp);
			}
		}


		printf("Case #%d: ", ++ca);
		cout << ans << endl;


	}
	return 0;
}
