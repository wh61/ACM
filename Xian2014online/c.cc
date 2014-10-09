#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>

using namespace std;

const int maxn = 55555;

int a[maxn];
int dp[maxn];
const int inf = 10000000;
int pre[maxn];
int nx[maxn];
int pos[maxn];



int main() {

	freopen("in.txt", "r", stdin);

	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) dp[i] = inf;
		dp[0] = a[0] = 0;
		map<int, int> mp;
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (mp.find(a[i]) != mp.end()) continue;
			mp[a[i]] = ++cnt;
		}
		for (int i = 1; i <= n; ++i) pre[i] = nx[i] = pos[i] = 0;
		for (int i = 1; i <= n; ++i) a[i] = mp[a[i]];
		int last = 0;
		int m = 0;
		for (m = 0; m * m <= n; ++m);
		for (int i = 1; i <= n; ++i) {
			if (pos[a[i]] == 0) {
				pos[a[i]] = i;
				pre[i] = last;
				nx[last] = i;
				last = i;
			} else {
				int p = pos[a[i]];
				if (last != p) {
					nx[pre[p]] = nx[p];
					pre[nx[p]] = pre[p];
					pos[a[i]] = i;
					pre[i] = last;
					nx[last] = i;
					last = i;
				} else {
					last = pre[p];
					nx[pre[p]] = nx[p];
					pre[nx[p]] = pre[p];
					pos[a[i]] = i;
					pre[i] = last;
					nx[last] = i;
					last = i;
				}
			}
			int cnt = 0;
			for (int j = last; true; j = pre[j]) {
				if (cnt > m) break;
				dp[i] = min(dp[i], dp[j] + cnt * cnt);
				if (j == 0) break;
				cnt++;
			}
		}
		printf("%d\n", dp[n]);
	}


	return 0;
}
