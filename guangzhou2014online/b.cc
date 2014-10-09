#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>


using namespace std;

struct node {
	int l, r;
	int val;
	int add;
}tree[4000002];

void build(int i, int left, int right) {
	node &p = tree[i];
	p.l = left;
	p.r = right;
	p.add = -1;
	p.val = 0;
	if (left == right) return;
	int mid = (p.l + p.r) / 2;
	build(i << 1, left, mid);
	build(i << 1 | 1, mid + 1, right);
}

void update(int i, int left, int right, int val) {
	node &p = tree[i];
	if (p.l == left && p.r == right) {
		p.add = val;
		p.val = val;
		return;
	}
	node &pl = tree[i << 1];
	node &pr = tree[i << 1 | 1];
	if (p.add != -1) {
		pl.val = pl.add = p.add;
		pr.val = pr.add = p.add;
		p.val = p.add;
		p.add = -1;
	}
	int mid = (p.l + p.r) / 2;
	if (right <= mid) {
		update(i << 1, left, right, val);
	} else if (left > mid) {
		update(i << 1 | 1, left, right, val);
	} else {
		update(i << 1, left, mid, val);
		update(i << 1 | 1, mid + 1, right, val);
	}
	p.val = pl.val | pr.val;
}


void query(int i, int left, int right, int& ans) {
	node &p = tree[i];
	if (p.l == left && p.r == right) {
		if (p.add != -1) p.val = p.add;
		ans |= p.val;
		return;
	}
	node &pl = tree[i << 1];
	node &pr = tree[i << 1 | 1];
	if (p.add != -1) {
		pl.val = pl.add = p.add;
		pr.val = pr.add = p.add;
		p.val = p.add;
		p.add = -1;
	}
	int mid = (p.l + p.r) / 2;
	if (right <= mid) {
		query(i << 1, left, right, ans);
	} else if (left > mid) {
		query(i << 1 | 1, left, right, ans);
	} else {
		query(i << 1, left, mid, ans);
		query(i << 1 | 1, mid + 1, right, ans);
	}
	p.val = pl.val | pr.val;
}




int main() {

	freopen("in.txt", "r", stdin);

	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		if (n == 0 && m == 0) break;
		build(1, 1, n);

		for (int k = 0; k < m; ++k) {
			char str[4];
			scanf("%s", str);
			if (str[0] == 'P') {
				int x, y, z;
				scanf("%d%d%d", &x, &y, &z);
				z--;
				//update(1, x, y, 0);
				update(1, x, y, 1 << z);

			} else {
				int x, y, z;
				scanf("%d%d", &x, &y);
				int ans = 0;
				query(1, x, y, ans);
				int cnt = 0;
				for (int i = 0; i < 30; ++i) {
					if ((ans >> i) & 1) {
						if (cnt) printf(" ");
						printf("%d", i + 1);
						cnt++;
					}
				}
				puts("");
			}
		}

	}
	return 0;
}
