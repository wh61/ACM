#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 111111;

int a[maxn];
int g[maxn], f[maxn];
int G[maxn], F[maxn];
typedef long long LL;

int main() {

	freopen("in.txt", "r", stdin);

	int n;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 0; i <= 100000; ++i) {
			F[i] = n + 1;
			G[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			if (F[a[i]] == n + 1) {
				f[i] = i;
			} else f[i] = F[a[i]];
			for (int j = 1; j * j <= a[i]; ++j) if (a[i] % j == 0) {
				F[j] = i;
				F[a[i] / j] = i;
			}
		}
		for (int i = n; i > 0; --i) {
			if (G[a[i]] == 0) {
				g[i] = i;
			} else g[i] = G[a[i]];
			for (int j = 1; j * j <= a[i]; ++j) if (a[i] % j == 0) {
				G[j] = i;
				G[a[i] / j] = i;
			}
		}

		LL ans = 0;
		for (int i = 1; i <= n; ++i) {
			LL tmp1 = a[f[i]];
			LL tmp2 = a[g[i]];
			ans += tmp1 * tmp2;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
