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
void init() {
	tot = 0;
	memset(st, 0, sizeof(st));
}

inline void add(int i, int a, int b) {
	ve[i] = b;
	nx[i] = st[a];
	st[a] = i;
}

void spfa(int n, int s, int *dist) {
	for (int i = 0; i < n; ++i) {
		dist[i] = inf;
		inq[i] = false;
	}
	dist[s] = 0;
	queue<int> q;
	inq[s] = true;
	q.push(s);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		inq[v] = false;
		for (int i = st[v]; i; i = nx[i]) {
			int v_ = ve[i];
			if (dist[v] + 1 < dist[v_]) {
				dist[v_] = dist[v] + 1;
				if (!inq[v_]) {
					q.push(v_);
					inq[v_] = true;
				}
			}
		}
	}
}

int u[maxn * maxn], v[maxn * maxn];

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
			u[i] = x;
			v[i] = y;
		}
		for (int i = 0; i < n; ++i) {
			spfa(n, i, dis[i]);
		}

		int ans = inf;

		for (int i = 0; i < m; ++i) {
			int x = u[i], y = v[i];

		}


		printf("Case %d: ", ++ca);
		if (ans == inf) {
			puts("impossible");
		} else printf("%d\n", ans);
	}
}
