#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 555555;


typedef long long LL;

struct node {
	int l, r;
	int mi, mx;
	LL cnt;
}tree[maxn * 2 * 4];

const int inf = 1000000000;

void buildTree(int i, int left, int right) {
	node& p = tree[i];
	p.l = left;
	p.r = right;
	if (left == right) {
		p.mx = p.cnt = 0;
		p.mi = inf;
		return;
	}
	int mid = (left + right) / 2;
	buildTree(i << 1, left, mid);
	buildTree(i << 1 | 1, mid + 1, right);
	node &pl = tree[i << 1];
	node &pr = tree[i << 1 | 1];
	p.mx = max(pl.mx, pr.mx);
	p.mi = min(pl.mi, pr.mi);
}


//1 max, 2 min, 3 cnt
void update(int i, int pos, int val) {
	node& p = tree[i];
	if (p.l == p.r) {
		p.mi = min(p.mi, val);
		p.mx = max(p.mx, val);
		p.cnt++;
		return;
	} else {
		int mid = (p.l + p.r) / 2;
		if (pos <= mid) update(i << 1, pos, val);
		else update(i << 1 | 1, pos, val);
	}
	node &pl = tree[i << 1], &pr = tree[i << 1 | 1];
	p.mi = min(pl.mi, pr.mi);
	p.mx = max(pl.mx, pr.mx);
	p.cnt = pl.cnt + pr.cnt;
}


void query(int i, int left, int right, int& ans, int type) {
	node &p = tree[i];
	if (left == p.l && p.r == right) {
		if (type == 3) ans += p.cnt;
		if (type == 2) ans = min(ans, p.mi);
		if (type == 1) ans = max(ans, p.mx);
	} else {
		int mid = (p.l + p.r) / 2;
		if (right <= mid) query(i << 1, left, right, ans, type);
		else if (left > mid) query(i << 1 | 1, left, right, ans, type);
		else {
			query(i << 1, left, mid, ans, type);
			query(i << 1 | 1, mid + 1, right, ans, type);
		}
	}
}

int a[maxn];
int p_[maxn];
LL dd[maxn];
LL ni[maxn];

struct position {
	int pos, id;
	position(int pos_, int id_): pos(pos_), id(id_) {}
	position() {}
};

bool cmp(const position& a, const position& b) {
	return a.pos < b.pos;
}

int main() {

	freopen("in.txt", "r", stdin);

	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= m; ++i) scanf("%d", p_ + i);
		buildTree(1, 1, 1000001);
		LL total = 0;
		for (int i = n; i > 0; --i) {
			update(1, a[i], 0);
			int ans = 0;
			if (a[i] > 1) query(1, 1, a[i] - 1, ans, 3);
			ni[i] = ans;
			total += ni[i];
		}
		vector<position> v;
		buildTree(1, 1, n);
		for (int i = 1; i <= m; ++i) {
			int pos = p_[i];
			int mx = 0;
			if (pos > 1) query(1, 1, pos, mx, 1);
			if (mx >= a[pos]) {

			} else {
				v.push_back(position(pos, i));
				update(1, pos, a[pos]);
			}
		}

		sort(v.begin(), v.end(), cmp);

		int sz = v.size();

		buildTree(1, 1, 1000001);

		int ind = 0;

		memset(dd, 0 ,sizeof(dd));

		for (int i = 1; i <= n; ++i) {
			while (ind < sz && v[ind].pos <= i) {
				update(1, a[v[ind].pos], v[ind].id);
				ind++;
			}
			int ans = inf;
			query(1, a[i], 1000001, ans, 2);
			if (ans == inf) continue;
			dd[ans] += ni[i];
		}
		printf("%lld\n", total);
		for (int i = 1; i <= m; ++i) {
			total -= dd[i];
			printf("%lld\n", total);
		}
	}
	return 0;
}
