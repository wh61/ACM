#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

#define maxn 555

const int inf = 10000000;

int dist[maxn][maxn], mat[maxn][maxn], ans;

int mincycle(int n) {

	int dist[n][n], ans = inf;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dist[i][j] = mat[i][j];
		}
	}

	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= k - 1; ++i) {
			for (int j = i + 1; j <= k - 1; ++j) {
				ans = min(ans, dist[i][j] + mat[i][k] + mat[k][j]);
			}
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}

	}

	return ans;
}


int main() {
	freopen("in.txt", "r", stdin);
	int T, ca = 0;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) mat[i][j] = inf;
		for (int i = 1; i <= n; ++i) mat[i][i] = 0;
		for (int i = 0; i < m; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			x++;
			y++;
			mat[x][y] = 1;
			mat[y][x] = 1;
		}



	printf("Case %d: ", ++ca);
	int ans = mincycle(n);
	if (!(ans < inf)) {
		puts("impossible");
	} else printf("%d\n", ans);




	}


	return 0;
}
