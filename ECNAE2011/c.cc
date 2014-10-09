#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const size_t maxn =2555;
const size_t maxb =555;


int r[maxn][maxb];

bool ok[maxn];

int b, n;

int get(int lhs, int rhs) {
	int win = 0;
	for (int i = 0; i < b; ++i) {
		if (r[lhs][i] < r[rhs][i]) {
			win++;
		}
	}
	if (win * 2 > b) return 1;
	if (win * 2 == b) return 0;
	return -1;
}




int main() {

	freopen("in.txt", "r", stdin);


	int ca = 0;
	while (scanf("%d%d", &b, &n) != EOF) {
		if (b == 0 && n == 0) break;
		for (int i = 0; i < b; ++i) {
			for (int j = 0; j < n; ++j) {
				int tmp;
				scanf("%d", &tmp);
				r[tmp][i] = j;
			}
		}
		memset(ok, true, sizeof(ok));
		for(int i = 0; i < n; ++i) {
			if (!ok[i]) continue;
			for (int j = i + 1; j < n; ++j) {
				if (get(i, j) == 0) {
					ok[i] = false;
					ok[j] = false;
					break;
				} else if (get(i, j) == 1) {
					ok[j] = false;
				} else {
					ok[i] = false;
					break;
				}
			}
		}

		int ans = true, c = -1;
		for (int i = 0; i < n; ++i) {
			if (ok[i]) {
				c = i;
			}
		}
		if (c == -1) {
			ans = false;
		} else {
			for (int i = 0; i < n; ++i) {
				if (i != c) {
					if (get(c, i) != 1) ans = false;
				}
			}
		}
		printf("Case %d: ", ++ca);
		if (ans) {
			printf("%d\n", c);
		} else {
			puts("No Condorcet winner");
		}
	}
	return 0;
}
