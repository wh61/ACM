#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const size_t maxn = 10005;
const size_t maxm = 256;

int cnt[maxn][maxm];
int a[maxn];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, m, K;
	scanf("%d%d", &n, &K);
	memset(cnt, 0 ,sizeof(cnt));
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	m = 0;
	map<int, int> mp;
	for (int i = 1; i <= n; ++i) {
		if (mp.find(a[i]) == mp.end()) {
			mp[a[i]] = m++;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < m; ++j) {
			cnt[i][j] = cnt[i - 1][j];
		}
		int val = mp[a[i]];
		cnt[i][val]++;
	}
	for (int i = 0; i < K; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		int ans = 0;
		for (int j = 0; j < m; ++j) {
			if (cnt[y][j] - cnt[x - 1][j] > 0) {
				ans++;
			}
		}
		printf("%d\n", ans);
	}






	return 0;
}
