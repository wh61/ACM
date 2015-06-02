#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>


using namespace std;

const int maxn = 555;

int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

int mp[maxn][maxn];


bool update(int n, int m) {
	int flag = false;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int cnt = 0;
			for (int k = 0; k < 4; ++k) {
				cnt += mp[i + dx[k]][j + dy[k]];
			}
			bool change = false;
			if (cnt > 2) {
				change = true;
			} else if (cnt == 2) {
				if ((mp[i + 1][j] && mp[i - 1][j]) || (mp[i][j - 1] && mp[i][j + 1])) {

				} else {
					change = true;
				}
			}
			if (change && mp[i][j] == 0) {
				mp[i][j] = 1;
				flag = true;
			}
		}
	}
	return flag;
}

int main() {
	freopen("1003.in", "r", stdin);
	int T, ca = 0;
	scanf("%d", &T);
	while (T--) {
		int n, m, K;
		scanf("%d%d%d", &n, &m, &K);
		memset(mp, 0, sizeof(mp));
		for (int i = 0; i < K; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			mp[x][y] = 1;
		}
		while (update(n, m));
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				ans += mp[i][j];
			}
		}
		printf("Case #%d:\n%d\n", ++ca, ans);
	}
	return 0;
}
