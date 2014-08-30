#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 11111;
const int maxb = 18;

int dep[maxn], sum[maxn], dfn[maxn], dfn_[maxn];
int dfnCnt;
int fa[maxn];
int g[maxn][maxb];

int st[maxn], nx[maxn * 2], ve[maxn * 2];
int visited[maxn];

int eCnt;

inline add(int i ,int a, int b) {
	ve[i] = b;
	nx[i]= st[a];
	st[a] = i;
}

void dfs(int v) {
	visited[v] = true;
	dfs[v] = ++dfnCnt;
	g[v][0] = fa[v];
	sum[v] = 1;
	for (int i = 1; i < maxb; ++i) {
		g[v][i] = g[g[v][i - 1]][i - 1];
	}
	for (int i = st[v]; i; i = nx[i]) {
		if (visited[ve[i]]) continue;
		fa[ve[i]] = v;
		dep[ve[i]] = dep[v] + 1;
		dfs(ve[i]);
		sum[v] += sum[ve[i]];
	}
	dfn_[v] = dfnCnt;
}


inline int getUp(int v, int dis) {
	for (int i = maxb - 1; i >= 0; --i) {
		if ((dis >> i) & 1 == 0) continue;
		v = g[v][i];
	}
	return v;
}


inline int getLca(int u, int v) {
	if (dep[u] > dep[v]) {
		u = getUp(u, dep[u] - dep[v]);
	} else {
		v = getUp(v, dep[v] - dep[u]);
	}
	if (u == v) return u;
	for (int i = maxb - 1; i >= 0; i--) {
		if (g[u][i] == g[v][i]) continue;
		u = g[u][i];
		v = g[v][i];
	}
	return fa[u];
}

inline int getDis(int u, int v) {
	int lca = getLca(u, v);
	return dep[u] + dep[v] - dep[lca] * 2;
}

inline pair<int, int> getMiddle(int u, int v) {
	int dis = getDis(u, v);
	if (dis & 1) {
		if (dep[u] == dep[v]) {
			return make_pair(getUp(u, dis / 2), getUp(v, dis / 2));
		} else {
			int uv;
			if (dep[u] > dep[v]) uv = u; else uv = v;
			int tmp = getUp(uv, dis / 2);
			return make_pair(tmp, fa[tmp]);
		}
	} else {
		int uv;
		if (dep[u] > dep[v]) uv = u; else uv = v;
		int tmp = getUp(uv, dis / 2);
		return make_pair(tmp, 0);
	}
}


struct node {
	int v;
	int id;
	int dep;
	node() {}
	node(int v_, int id_,int dep_):v(v_), id(id_), dep(dep_) {}
};

bool cmp(const node &a, const node &b) {
	return a.dep < b.dep;
}


inline void getAns(int A, int B, int C) {
	ans[3];
	vector<node> v;
	v.push_back(node(A, 0, dep[A]));
	v.push_back(node(B, 1, dep[B]));
	v.push_back(node(C, 2, dep[C]));
	sort(v.begin(), v.end(), cmp);

	int a, b, c;
	a = v[0].v;
	b = v[1].v;
	c = v[2].v;

	if (dep[a] == dep[c]) {
		for (int i = 0; i < 2; ++i) {
			int val = 0;
			int lca = 0;
			for (int j = 0; j < 2; ++j) if (i != j) {
				int tmp = getLca(v[i].v, v[j].v);
				if (dep[tmp] > val) val = dep[tmp], lca = tmp;
			}
			int u = v[i].v;
			int step = dep[u] - dep[lca] - 1;
			u = getUp(u, step);
			ans[v[i].id] = sum[u];
		}
	} else if (dep[a] == dep[b] && dep[b] < dep[c]) {
		int lcaab = getLca(a, b);
		int step = dep[a] - dep[lcaab] - 1;
		int aa = getUp(a, step);
		int bb = getUp(b, step);
		ans[v[0].id] = sum[aa];
		ans[v[1].id] = sum[bb];
		pair<int, int> pr = getMiddle(a, c);
		int md = pr.first;
		ans[v[2].id] = sum[1] - sum[md];
	} else if (dep[a] < dep[b] && dep[b] == dep[c]) {

	}

}



int main() {


	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i <= n; ++i) st[i] = 0;
		eCnt = 0;
		fa[1] = 0;
		for (int i = 0; i < maxb; ++i) g[0][i] = g[1][i] = 0;
		for (int i = 1; i < n; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			add(++eCnt, x, y);
			add(++eCnt, y, x);
		}

		memset(visited, 0, sizeof(visited));
		dfnCnt = 0;
		dep[1] = 1;
		dfs(1);



	}
	return 0;
}
