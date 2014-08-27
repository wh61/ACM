#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxn 1005
#define maxm 30005
#define inf 0x3fffffff

struct Edge{int u, v, cap, cost, x;}E[maxn];
int e, l[maxn];
inline void init() {e = 0; memset(l, -1, sizeof(-1));}
inline void insert(int u, int v, int cap, int cost) {
	E[e].u = u, E[e].v = v; E[e].cap = cap; E[e].cost = cost; E[e].x = l[u]; l[u] = e++;
	E[e].u = v; E[e].v = u; E[e].cap = 0; E[e].cost = -cost; E[e].x = l[v]; l[v] = e++;


int q[20 * maxn], s, t, inq[maxn], dis[maxn], eid[maxn];

void min_cost_max_flow(int src, int sink, int &cap, int &cost) {
	cost = cap = 0;
	while (true) {
		for (int i = 0; i < maxn; ++i) dis[i] = inf;
		s = t = 0; q[t++] = src; inq[src] = 1; dis[src] = 0;
		while (s < t) {
			int u = q[s++];
			inq[u] = 0;
			for (int p = l[u]; p >= 0; p = E[p].x) {
				if (E[p].cap <= 0) continue;
				int v = E[p].v;
				if (dis[v]  > dis[u] + E[p].cost) {
					dis[v] = dis[u] + E[p].cost; eid[v] = p;
					if (inq[v] == 0) {
						inq[v] = 1;
						q[t++] = v;
					}
				}
			}
		}// end spfa;
		if (dis[sink] >= inf) return;
		int c = inf;
		for (int i = sink; i != src; i = E[eid[i]].u]) c = min(c, E[eid[i]].cap);
		cost += dis[sink] * c; cap += c;
		for (int i = sink; i != src; i = E[eid[i]].u) {
			int p = eid[i]; E[p].cap -= c; E[p ^ 1].cap += c;
		}
	}
}


int A[maxn];
int mp[55][555];




int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", A + i);

		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= A[i]; ++j) {
				mp[i][j] = ++cnt;
			}
		}
		int s = cnt + 1, t = cnt + 2;
		init();
		for (int i = 1; i <= n; ++i) {
			insert(s, mp[i][0], inf, 0);
			insert(mp[i][a[i]], 1, 0);
			for (int j = a[i]; j > 0; --j) {
				insert(mp[i][j], mp[i][j - 1], inf, 0);
			}
		}

		for (int i = 0; i < m; ++i) {
			int c, l1, d, l2;
			scanf("%d%d%d%d", &c, &l1, &d, &l2);
			insert()
		}


	}
	return 0;
}
