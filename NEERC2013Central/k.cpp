#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 3333;

int dp[maxn][1111];
int x[maxn], y[maxn];
int L[maxn];


inline int _gcd(int a, int b) {
	int tmp;
	while (b > 0) {
		tmp = a;
		a = b;
		b = tmp % b;
	}
	return a;
}


const int mask = (1 << 30) - 1;


int H[maxn];
int ok[maxn];



int main() {

	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int n, m;

	cin >> n >> m;

	int h = 0;

	memset(ok, false, sizeof(ok));

	for (int i = 1; i <= m; ++i) {
		cin >> x[i] >> y[i];
		ok[x[i]] = true;
		h = max(h, y[i]);
	}

	x[0] = 0;
	y[0] = h;
	x[m + 1] = n;
	y[m + 1] = h;

	memset(L, 0, sizeof(L));

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= m + 1; ++j) {
			if (x[j] < i) {
				L[i] = x[j];
				H[i] = y[j];
			} else break;
		}
	}

	for (int i = 0; i <= h; ++i) {
		dp[0][i] = 1;
	}

	L[x[1]] = 0;

	for (int i = x[1] + 1; i <= n; ++i) {
		for (int j = 0; j <= h; ++j) {
			dp[i][j] = 0;
			if (ok[i]) continue;
			int dx = i - L[i], dy = H[i] - j;
			if (dy < 1) break;
			if (dx < 1) break;
			int gcd = _gcd(dx, dy);
			dx /= gcd;
			dy /= gcd;
			int xx = L[i], yy = H[i];
			for (int k = 0; k <= 1000; ++k) {
				xx -= dx;
				yy -= dy;
				if (xx < L[L[i]] || yy < 0) {
					break;
				}
				dp[i][j] = (dp[i][j] + dp[xx][yy]) & mask;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i <= h; ++i) {
		ans = (ans + dp[n][i]) & mask;
	}
	printf("%d\n", ans);


	return 0;
}
