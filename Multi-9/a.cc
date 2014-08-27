#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

typedef long long LL;

const int maxn = 111111;
int a[maxn];
int f[maxn];
int c[maxn];
LL dp[maxn];

int main() {

	freopen("in.txt", "r", stdin);


	int n;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", c + i);
		}
		c[0] = 0;
		map<LL, int> mp;
		LL tmp = 0;
		for (int i = n; i > 0; --i) {
			mp[tmp] = i;
			tmp += (LL)a[i];
		}
		tmp = 0;
		for (int i = 1; i <= n; ++i) {
			int RR = n + 2;
			if (mp.find(tmp) != mp.end()) RR = mp[tmp];
			f[i] = RR;
			tmp += (LL)a[i];
		}
		vector<int> v;
		for (int i = 1; i <= n; ++i) {
			if (f[i] == n + 2 || f[i] < i - 1) continue;
			v.push_back(i);
		}
		int sz = v.size();
		dp[sz] = 0;
		for (int i = sz - 1; i >= 0; --i) {
			int L = v[i];
			dp[i] = c[f[L] - L + 1];
			for (int j = i + 1; j < sz; ++j) {
				LL L_ = v[j];
				int dL = L_ - L;
				int dR = f[L] - f[L_];
				dp[i] = min(dp[i], dp[j] + c[dL] + c[dR]);
			}
		}
		int ans = dp[0];
		printf("%d\n", ans);
	}
	return 0;
}
