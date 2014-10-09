#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;


const int maxn = 22;

int a[maxn];
int num[maxn];

typedef long long LL;

LL g[maxn][maxn], f[maxn][maxn];

const LL inf = 2000000000000000000;
LL p10[maxn];
int main() {

	freopen("in.txt", "r", stdin);


	int T;


	p10[0] = 1;
	for (int i = 1; i <= 18; ++i) p10[i] = p10[i - 1] * 10;

	cin >> T;



	while (T--) {
		LL val;
		cin >> val;


		if (val == 0) {
			cout << 0 << endl;
			continue;
		}







		LL tmp = val;
		int bit = 0;
		while (tmp != 0) {
			num[++bit] = tmp % 10;
			tmp /= 10;
		}

		if (bit == 1) {
			cout << val << endl;
			continue;
		}

		num[bit + 1] = 10;

		LL c[maxn];
		c[bit] = c[1] = num[bit] - 1;


		LL rs = 0;

		LL rs_tmp = 0;

		for (int i = 2; i < bit; ++i) c[i] = 9;
		for (int i = bit; i > 0; --i) rs_tmp = rs_tmp * 10 + c[i];

		rs = max(rs, rs_tmp);

		rs_tmp = 0;

		for (int i = 1; i < bit; ++i) rs_tmp = rs_tmp * 10 + 9;

		rs = max(rs, rs_tmp);


		for (int mid = 1; mid <= bit; ++mid) {
			int m = 0;

			LL ans = 0;
			for (int i = bit; i >= mid; --i) {
				if (num[i] != num[i + 1]) {
					a[++m] = num[i];
				}
				ans = ans * 10 + num[i];
			}
			ans *= p10[mid - 1];

			for (int i = 0; i <= m; ++i) {
				for (int j = 0; j <= mid; ++j) {
					g[i][j] = f[i][j] = -inf;
				}
			}
			g[0][0] = f[0][0] = 0;

			//

			for (int i = 1; i <= m; ++i) {
				for (int j = i; j < mid; ++j) {
					if (a[i] == num[j]) {
						f[i][j] = max(f[i - 1][j - 1], f[i][j - 1]) + a[i] * p10[j - 1];
						g[i][j] = f[i][j];
					}
					if (a[i] > num[j]) {
						f[i][j] = -inf;
						g[i][j] = max(g[i - 1][j - 1], g[i][j - 1]) + a[i] * p10[j - 1];
					}
					if (a[i] < num[j]) {
						f[i][j] = g[i][j] = max(g[i - 1][j - 1], g[i][j - 1]) + a[i] * p10[j - 1];
					}
				}
			}

			ans += max(f[m][mid - 1], f[m - 1][mid - 1]);

			rs = max(rs, ans);


//////////////////

			m = 0;

			ans = 0;

			int num_[maxn];

			for (int i = 1; i <= bit; ++i) num_[i] = num[i];

			LL tval = 0;

			for (int i = bit; i >= mid; --i) tval = tval * 10 + num[i];

			tval--;


			for (int i = mid; i <= bit; ++i) num[i] = tval % 10, tval /= 10;

			int dt = 0;

			if (num[bit] == 0) dt = 1;

			bit -= dt;


			for (int i = bit; i >= mid; --i) {
				if (num[i] != num[i + 1]) {
					a[++m] = num[i];
				}
				ans = ans * 10 + num[i];
			}
			ans *= p10[mid - 1];

			for (int i = 0; i <= m; ++i) {
				for (int j = 0; j <= mid; ++j) {
					g[i][j] = f[i][j] = -inf;
				}
			}
			g[0][0] = f[0][0] = 0;

			//

			for (int i = 1; i <= m; ++i) {
				for (int j = i; j < mid; ++j) {
					if (a[i] == num[j]) {
						f[i][j] = max(f[i - 1][j - 1], f[i][j - 1]) + a[i] * p10[j - 1];
						g[i][j] = f[i][j];
					}
					if (a[i] > num[j]) {
						f[i][j] = -inf;
						g[i][j] = max(g[i - 1][j - 1], g[i][j - 1]) + a[i] * p10[j - 1];
					}
					if (a[i] < num[j]) {
						f[i][j] = g[i][j] = max(g[i - 1][j - 1], g[i][j - 1]) + a[i] * p10[j - 1];
					}
				}
			}

			ans += max(g[m][mid - 1], g[m - 1][mid - 1]);

			rs = max(rs, ans);


			bit += dt;


			for (int i = 1; i <= bit; ++i) num[i] = num_[i];




/////////////////////////








		}
		cout << rs << endl;
	}
}
