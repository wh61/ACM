#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 3003;

int dp[maxn][maxn];
int x[maxn], y[maxn];
int Lh[maxn], Rh[maxn];
int height[maxn];

/*

inline int gcd_(int a, int b) {
	int tmp,ans = 1;
	while (b > 0) {
		if (b>a) {
			tmp = b; b = a; a = tmp;
		}
		if ((a&1)&&(b&1)) {
			tmp = a;
			a = b;
			b = tmp-a;
			continue;
		}
		if ((a&1)&&(!(b&1))) {
			b >>= 1;
			continue;
		}
		if ((!(a&1))&&(b&1)) {
			a >>= 1;
			continue;
		}
		a>>=1; b>>=1;
		ans <<= 1;
	}
	return ans * b;
}
*/


inline int _gcd(int a, int b) {
	int tmp;
	while (b > 0) {
		tmp = a;
		a = b;
		b = tmp % b;
	}
	return a;
}

int nx[maxn];

const int mask = (1 << 30) - 1;
bool ok[maxn];


int main() {

	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int n, m;

	cin >> n >> m;
	memset(ok, 0, sizeof(ok));

	x[0] = -1;
	y[0] = 3000;
	x[m + 1] = n + 1;
	y[m + 1] = 3000;
	y[m + 2] = 3000;

	for (int i = 1; i <= m; ++i) {
		cin >> x[i] >> y[i];
		ok[x[i]] = true;
	}

	nx[0] = 0;
	for (int i = 1; i <= m; ++i) {
		nx[i] = x[i - 1] + 1;
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= m + 1; ++j) {
			if (x[j] < i) {
				Lh[i] = j;
			} else break;
		}
		for (int j = m + 1; j >= 0; --j) {
			if (x[j] > i) {
				Rh[i] = j;
			} else break;
		}
	}
	height[n] = 3000;

	for (int i = 0; i < x[1]; ++i) {
		for (int j = 0; j < y[1]; ++j) {
			int g = _gcd(x[1] - i, y[1] - j);
			int di = i / g, dj = j / g;
			dp[x[1] - di][y[1] - dj] = 1;
		}
	}

	for (int i = x[1] + 1; i <= n; ++i) {
		if (ok[i]) continue;
		height[i] = min(y[Lh[i]], y[Rh[i]]) - 1;
		int ind = Lh[i];
		for (int j = 0; j <= height[i]; ++j) {
			dp[i][j] = 0;
			int dx = i - x[ind], dy = y[ind] - j;
			int gcd = _gcd(dx, dy);
			dx /= gcd;
			dy /= gcd;
			int xx = x[ind], yy = y[ind];
			for (int k = 0; k <= 3000; ++k) {
				xx -= dx;
				yy -= dy;
				if (xx < nx[ind] || y < 0) {
					break;
				}
				dp[i][j] = (dp[i][j] + dp[xx][yy]) & mask;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i <= 3000; ++i) {
		ans = (ans + dp[n][i]) & mask;
	}
	printf("%d\n", ans);


	return 0;
}
