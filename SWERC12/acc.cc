#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>


using namespace std;

const int maxn = 555;
int dis[maxn][maxn];
bool inq[maxn];

const int inf = 100000000;

int st[maxn], nx[maxn * maxn], ve[maxn * maxn];
int tot;
int fa[maxn];

void init() {
	tot = 0;
	memset(st, 0, sizeof(st));
}

inline void add(int i, int a, int b) {
	ve[i] = b;
	nx[i] = st[a];
	st[a] = i;
}


int step[maxn];

int main() {

	freopen("in.txt", "r", stdin);

	int T, ca = 0;;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		init();
		for (int i = 0; i < m; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			add(++tot, x, y);
			add(++tot, y, x);
		}


		int ans = inf;

		for (int i = 0; i < n; ++i) {
			for (int i = 0; i < n; ++i) inq[i] = false;
			int s = i;
			step[s] = 0;
			queue<int> q;
			q.push(s);
			inq[s] = true;

			while (!q.empty()) {
				int v = q.front();
				q.pop();
				for (int i = st[v]; i; i = nx[i]) {
					if (!inq[ve[i]]) {
						inq[ve[i]] = true;
						step[ve[i]] = step[v] + 1;
						q.push(ve[i]);
						fa[ve[i]] = v;
					} else if (ve[i] != fa[v]){
							ans = min(ans, step[ve[i]] + step[v] + 1);
					}

				}
			}

		}




		printf("Case %d: ", ++ca);
		if (ans == inf) {
			puts("impossible");
		} else printf("%d\n", ans);
	}
}
