#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 55;
const int maxT = 1111;

char s[maxn][maxn];


int a[maxT][maxn][maxn];
int b[maxn][maxn];



int main() {

	freopen("in.txt", "r", stdin);


	int T, ca = 0;
	int n, m, F, K;
	scanf("%d", &T);
	while (T--) {

		vector<pair<int, int > > v[maxT];

		for (int i = 0; i < maxT; ++i) v[i].clear();


		scanf("%d%d%d%d", &n, &m, &F, &K);
		for (int i = 0; i < n; ++i) {
			scanf("%s", s[i]);
		}
		for (int i = 0; i < K; ++i) {
			int t, x, y;
			scanf("%d%d%d", &t, &x, &y);
			v[t].push_back(make_pair(x, y));
		}

		for (int i = 0; i < maxn; ++i)
			for (int j = 0; j < maxn; ++j) a[0][i][j] = 0;

		memset(b, 0, sizeof(b));

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				a[0][i][j] = s[i - 1][j - 1] - '0';


		for (int t = 1; t <= F; ++t) {

			for (int i = 0; i <= n + 1; ++i)
				for (int j = 0; j <= m + 1; ++j)
					a[t][i][j] = 0;

		    // time begin;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					if (b[i][j]) {
						a[t][i][j] = 0;
						continue;
					}
					int tmp = 0;
					for (int di = -1; di <= 1; ++di)
						for (int dj = -1; dj <= 1; ++dj) {
							if (di == 0 && dj == 0) continue;
							tmp += a[t - 1][i + di][j + dj];
						}
					if (a[t - 1][i][j] == 1) {
						if (tmp < 2) a[t][i][j] = 0;
						else if (tmp > 3) a[t][i][j] = 0;
						else a[t][i][j] = 1;
					} else {
						if (tmp == 3) a[t][i][j] = 1; else a[t][i][j] = 0;
					}
				}
			}

			// time end;

			int sz = v[t].size();
			for (int i = 0; i < sz; ++i) {
				int x = v[t][i].first, y = v[t][i].second;
				a[t][x][y] = 0;
				b[x][y] = 1;
			}

		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (b[i][j]) {
					printf("X");
				} else {
					printf("%d", a[F][i][j]);
				}
			}
			puts("");
		}


	}
	return 0;
}
