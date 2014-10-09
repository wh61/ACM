#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;


const size_t maxn = 104;

int w[maxn][maxn];
int seq[maxn];

int n;

int f[maxn], g[maxn];
const int inf = 100000000;
bool inq[maxn];

int dis1[maxn][maxn], cnt[maxn][maxn];

void spfa(int s) {
	for (int i = 0; i < n; ++i) {
		f[i] = inf;
		g[i] = 0;
		inq[i] = false;
	}
	inq[s] = true;
	f[s] = 0;
	g[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int v = q.front();
		inq[v] = false;
		q.pop();
		for (int ve = 0; ve < n; ++ve) if (v != ve){
			if (f[v] + w[v][ve] < f[ve]) {
				f[ve] = f[v] + w[v][ve];
				g[ve] = g[v];
				if (!inq[ve]) {
					q.push(ve);
					inq[ve] = true;
				}
			} else if (f[v] + w[v][ve] == f[ve]) {
				if (g[ve] == 0) {
					g[ve] = 1;
					if (!inq[ve]) {
						q.push(ve);
						inq[ve] = true;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		dis1[s][i] = f[i];
		cnt[s][i] = g[i];
	}
}




int main() {



	freopen("in.txt", "r", stdin);



	int m, ca = 0;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &w[i][j]);
				if (w[i][j] == 0 && i != j) w[i][j] = inf;
			}
		}
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			scanf("%d", seq + i);
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				dis1[i][j] = inf;
				cnt[i][j] = 0;
			}
		}
		int ans = 0;
		int ind = 0;
		int v = seq[0];
		while (true) {
			spfa(v);
			int *f = dis1[v];
			int *g = cnt[v];
			int dist = 0;
			int ve = -1;
			int nx_index = -1;
			for (int i = ind + 1; i < m; ++i) {
				int v1 = seq[i - 1], v2 = seq[i];
				dist += w[v1][v2];
				if (dist > f[v2]) {
					ve = v2;
					nx_index = i;
					break;
				} /*else if (f[v2] == dist && g[v2] > 0) {
					ve = v2;
					nx_index = i;
					break;
				} */else {

				}
			}
			if (nx_index == -1) {
				break;
			} else {
				ans++;
				v = ve;
				ind = nx_index;
			}
		}

		printf("Case %d: %d\n", ++ca, ans);

	}


	return 0;
}
