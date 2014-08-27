#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		int mx = 0;
		int tot = 0;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			int tmp;
			scanf("%d", &tmp);
			mx = max(tmp, mx);
			tot += tmp;
		}
		int ans1 = (tot - 1) / m + 1;
		int ans = max(mx, ans1);
		printf("%d\n", ans);
	}
	return 0;
}
