#include <iostream>
#include <cstdio>

using namespace std;

typedef long long LL;

const int maxn = 111111;

LL a[maxn];
LL b[maxn];
LL h[maxn];

int main() {


//	freopen("in.txt", "r", stdin);


	int n, m, K;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		scanf("%d", &m);
		for (int i = 0; i <= n; ++i) a[i] = b[i] = 0;
		for (int i = 0; i < m; ++i) {
			int L, R, D;
			scanf("%d%d%d", &L, &R, &D);
			a[R] += D;
			b[L] -= D;
		}
		scanf("%d", &K);
		LL decHP = 0;
		h[n + 1] = 0;
		for (int i = n; i > 0; --i) {
			decHP += a[i];
			h[i] = h[i + 1] + decHP;
			decHP += b[i];
		}

		int ans = 0;
		for (int i = 0; i < K; ++i) {
			LL HP;
			int x;
			scanf("%I64d%d", &HP, &x);
			if (HP > h[x]) ans++;
		}

		printf("%d\n", ans);
	}
	return 0;
}
