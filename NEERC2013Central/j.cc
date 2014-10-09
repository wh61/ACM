#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>


using namespace std;


#define maxn 11111
#define maxm 444444

struct Edge {int v, next; } E[maxm];
int e = 0;
struct AdjList {
	int l[maxn];
	void insert(int a, int b, int val = 0) {
		E[e].v = b; E[e].next = l[a]; l[a] = e++;
		E[e].v = a; E[e].next = l[b]; l[b] = e++;
	}
	void init() {
		memset(l, -1, sizeof(l));
	}
}adj, adj2;


struct bidirGraph {
	int dep[maxn], low[maxn], q[maxn];
	int *l; Edge *E;

	void _tarjan(int u, int D, int _i) {
		low[u] = dep[u] = D;
		for (int i = l[u];i >= 0; i = E[i].next) {
			if ((i ^ 1) == _i) continue;
			int v = E[i].v;
			if (dep[v] < 0) {
				_tarjan(v, D + 1, i);
				low[u] = min(low[u], low[v]);
			} else {
				low[u] = min(low[u], dep[v]);

			}
		}
	}

	bool qiao(int u, int v) {
		if (dep[u] > dep[v]) swap(u, v);
		return low[v] > dep[u];
	}

	int main(int n, int *_l, Edge *_E, int *label) {
		l = _l;
		E = _E;
		for (int i = 0; i < n; ++i) dep[i] = label[i] = -1;
		for (int i = 0; i < n; ++i) if (dep[i] < 0) _tarjan(i, 0, -1);
		int c = 0, s, t;
		for (int i = 0; i < n; ++i) {
			if (label[i] >= 0) continue;
			s = t = 0;
			q[t++] = i;
			label[i] = c;
			while (s < t) {
				int u = q[s++], v;
				for (int j = l[u]; j >= 0; j = E[j].next) {
					v = E[j].v;
					if (qiao(u, v) || label[v] >= 0) continue;
					q[t++] = v;
					label[v] = c;
				}
			}
			c++;
		}
		return c;
	}
}ins;


int label[maxn];

void rebuild(int n) {
	for (int i = 0; i < n; ++i) {
		for (int p = adj.l[i]; p >= 0; p = E[p].next) {
			int j = E[p].v;
			if (ins.qiao(i, j)) {
				adj2.insert(label[i], label[j]);

			}
		}
	}
}


int dep1[maxn], dep2[maxn];
int visited[maxn];
int node1[maxn], node2[maxn];

void dfs(int v) {
	visited[v] = true;
	int mx1 = 0, mx2 = 0;
	int n1 = v, n2 = v;
	for (int p = adj2.l[v]; p >= 0; p = E[p].next) {
		int ve = E[p].v;
		if (!visited[ve]) {
			dfs(ve);
			if (dep1[ve] + 1 > mx1) {
				mx2 = mx1;
				n2 = n1;
				mx1 = dep1[ve] + 1;
				n1 = node1[ve];
			} else if (dep1[ve] + 1 > mx2) {
				mx2 = dep1[ve] + 1;
				n2 = node1[ve];
			}
		}
	}
	dep1[v] = mx1;
	dep2[v] = mx2;
	node1[v] = n1;
	node2[v] = n2;
}



int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	e = 0;
	adj.init();
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		adj.insert(x, y);
	}
	adj2.init();
	for (int i = 0; i < n; ++i) label[i] = -1;
	int N = ins.main(n, adj.l, E, label);
	rebuild(n);

	memset(visited, 0, sizeof(visited));
	memset(dep1, 0, sizeof(dep1));
	memset(dep2, 0 ,sizeof(dep2));
	for (int i = 0; i < N; ++i) {
		node1[i] = node2[i] = i;
	}
	dfs(1);
	int mid = -1;
	int longest = -1;
	for (int i = 0; i < N; ++i) {
		if (dep1[i] + dep2[i] > longest) {
			longest = dep1[i] + dep2[i];
			mid = i;
		}
	}
	int v1 = node1[mid], v2 = node2[mid];
	int ans1 = -1, ans2 = -2;
	for (int i = 0; i < n; ++i) {
		if (label[i] == v1 && ans1 == -1) {
			ans1 = i + 1;
		}
		if (label[i] == v2) {
			ans2 = i + 1;
		}
	}
	printf("%d %d\n", ans1, ans2);

}


