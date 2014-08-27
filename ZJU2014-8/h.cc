#include <iostream>
#include <cstdio>
#include <cstring>


using namespace std;

const int maxn = 11111;


int c[maxn][2];
int cNum[maxn];
int w[maxn];

int a[maxn];



int main() {

	freopen("in.txt", "r", stdin);

	int ca = 0;
	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 2; i <= n; ++i) {
			scanf("%d", a + i);
		}
		a[1] = 0;
		int ans = 0;
		memset(c, 0, sizeof(c));
		memset(cNum, 0, sizeof(cNum));
		for (int i = n; i > 0; --i) {
			int tmp = a[i];
			c[tmp][cNum[tmp]++] = i;
			if (cNum[i] == 0) {
				w[i] = 1;
			} else if (cNum[i] == 1) {
				w[i] = w[c[i][0]];
			} else if (cNum[i] == 2) {
				int mi = min(w[c[i][0]], w[c[i][1]]);
				int mx = max(w[c[i][0]], w[c[i][1]]);
				w[i] = max(mi + 1, mx);
			}
		}
		for (int i = 1; i <= n; ++i) ans = max(ans, w[i]);
		printf("%d\n", ans);

	}

	return 0;
}
