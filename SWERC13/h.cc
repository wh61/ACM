#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int maxn = 111111;

int dp[maxn];

const int MOD = 21092013;

string S, T;

int nxL[maxn];
int nxR[maxn];
int u[maxn];

int main() {

	freopen("in.txt", "r",stdin);

	int CA, ca = 0;
	scanf("%d", &CA);
	while (CA--) {
		cin >> S;
		cin >> T;
		int sz = S.size();
		vector<char> v;
		for (int i = 0; i < sz; ++i) {
			if (S[i] == 'L') v.push_back('L');
			if (S[i] == 'R') v.push_back('R');
			if (S[i] == 'U') {
				if (v.size() > 0) v.pop_back();
			}
		}
		sz = T.size();
		int uCnt = 0;

		int ind = 0;

		for (int i = 0; i < sz; ++i) {
			if (T[i] == 'L' || T[i] == 'R') {

			} else u[++uCnt] = i;
		}

		dp[sz] = 0;
		nxL[sz] = sz;
		nxR[sz] = sz;
		for (int i = sz - 1; i >= 0; --i) {
			int nextL = nxL[i] = nxL[i + 1];
			int nextR = nxR[i] = nxR[i + 1];
			dp[i] = (dp[nextL] + dp[nextR] + 1) % MOD;
			if (T[i] == 'L') nxL[i] = i;
			if (T[i] == 'R') nxR[i] = i;
		}

		int m = v.size();

		int ans = 0;

		for (int up = 0; up <= m; ++up) {
			if (up > uCnt) break;
			if (up == 0) {
				ans += dp[nxL[0]] + dp[nxR[0]] + 1;
				ans %= MOD;
				continue;
			}
			char ch = v[m - up];
			if (ch == 'L') {
				ans += dp[nxR[u[up]]] + 1;
				ans %= MOD;
			} else {
				ans += dp[nxL[u[up]]] + 1;
				ans %= MOD;
			}
		}
        printf("Case %d: %d\n", ++ca, ans);
	}


	return 0;
}
