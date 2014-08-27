#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

const int maxn = 111111;


struct QueNode {
	int l, r;
	int id;
	QueNode(int l_, int r_, int id_):l(l_), r(r_), id(id_) {}
};

int a[maxn];
int g[maxn];
int c[maxn];


typedef long long LL;


LL ans[maxn];

vector<int> P[maxn];

int n, m, Q;


struct node {
	int l, r;
	LL val;
	int add;
}tree[maxn * 4];

inline void build(int i,int left, int right) {
	node &p = tree[i];
	p.l = left, p.r = right, p.add = 0, p.val = 0;
	if (left == right) return;
	int mid = (left + right) >> 1;
	build(i << 1, left, mid);
	build(i << 1 | 1, mid + 1, right);
}

inline void push_down(int i) {
	LL len = tree[i].r - tree[i].l + 1;
    tree[i].val += len * (LL)tree[i].add;
    if (len > 1) {
		tree[i << 1].add += tree[i].add;
		tree[i << 1 | 1].add += tree[i].add;
	}
	tree[i].add = 0;
}

inline void push_up(int i) {
	tree[i].val = tree[i << 1].val + tree[i << 1 | 1].val;
	tree[i].add = 0;
}

inline void update(int i, int left, int right, int v) {
	node &p = tree[i];
	push_down(i);
	if (left == p.l && right == p.r) {
		p.add += v;
		return;
	}
	int mid = (p.l + p.r) >> 1;
	if (right <= mid) {
		update(i << 1, left, right, v);

	} else if (left > mid) {
		update(i << 1 | 1, left, right, v);
	} else {
		update(i << 1, left, mid, v);
		update(i << 1 | 1, mid + 1, right, v);
	}
	push_down(i << 1);
	push_down(i << 1 | 1);
	push_up(i);
}


inline void query(int i,int left, int right, LL &ans) {
	node &p = tree[i];
	push_down(i);
	if (left == p.l && p.r == right) {
		ans += p.val;
		return;
	}
	int mid = (p.l + p.r) >> 1;
	if (right <= mid) {
		query(i << 1, left, right, ans);
	} else if (left > mid) {
		query(i << 1 | 1, left, right, ans);
	} else {
		query(i << 1, left, mid, ans);
		query(i << 1 | 1, mid + 1, right, ans);
	}
	push_down(i << 1);
	push_down(i << 1 | 1);
	push_up(i);
}

int last[maxn], pre[maxn];

vector<int> q[maxn];

void work(int g, vector<QueNode>& v) {
	for (int i = 1; i <= n; ++i) {
		if (a[i] % g == 0) c[i] = a[i] / g; else c[i] = -1;
	}

	build(1, 1, n);
	for (int i = 1; i <= n; ++i) q[i].clear();
	for (int i = 0; i < v.size(); ++i) q[v[i].r].push_back(i);
	for (int i = 0; i < maxn; ++i)
		last[i]= 0, pre[i] = 1;
	int lastm1 = 0;
	for (int i = 1; i <= n; ++i) {

		if (c[i] == -1) {
			lastm1 = i;
		} else {

			vector<int> &p = P[c[i]];
			int sz = p.size();
			for (int j = 0; j < sz; ++j) {
				if (last[p[j]] == i - 1) {
					last[p[j]] = i;
				} else {
					last[p[j]] = i;
					pre[p[j]] = i;
				}
			}
			int tmp = i + 1;
			for (int j = 0; j < sz; ++j) {
				tmp = min(tmp, pre[p[j]]);
			}
		//lastm1 + 1 -- tmp - 1;
			if (lastm1 + 1 < tmp) update(1, lastm1 + 1, tmp - 1, 1);
		}


		int sz = q[i].size();
		for (int j = 0; j < sz; ++j) {
			int ind = q[i][j];
			int l = v[ind].l, r = v[ind].r;
			LL da = 0;
			query(1, l, r, da);
			ans[v[ind].id] = da;
		}
	}
}







int main() {

	freopen("in.txt", "r", stdin);

	for (int i = 0; i < maxn; ++i) P[i].clear();

	for (int i = 2; i < maxn; ++i) {
		if (P[i].size() != 0) continue;
		for (int j = i; j < maxn; j += i) {
			P[j].push_back(i);
		}
	}

	while (scanf("%d%d%d", &n, &m, &Q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	//	for (int i = 1; i <= n; ++i) a[i] = 1;
		for (int i = 1; i <= m; ++i) scanf("%d", g + i);
		map<int, int> ind;
		for (int i = 1; i <= m; ++i) ind[g[i]] = i;

		vector<QueNode> v[55];
		for (int i = 1; i <= Q; ++i) {
			int l, r, gg;
			scanf("%d%d%d", &l, &r, &gg);
			int tmp = ind[gg];
			v[tmp].push_back(QueNode(l + 1, r, i));
		}

		for (int i = 1; i <= m; ++i) {
			work(g[i], v[i]);
		}

		for (int i = 1; i <= Q; ++i) {
			printf("%lld\n", ans[i]);
		}

	}

	return 0;
}
