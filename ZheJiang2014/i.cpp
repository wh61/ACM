#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>



using namespace std;

int CH;

struct DD {
	int num;
	DD *fail, *x[26];
	bool visited, inq;
	bool useful;
	int dfn, low;
	void init() {
		num = 0;
		useful = visited = inq = dfn = 0;
		memset(x, NULL, sizeof(x));
	}
}dd[120000], *que[120000];

struct ACAutoM {
	int e;
	DD *root;
	DD *_alloc() {dd[e].init(); return &dd[e++];}
	int dfnCnt, ans;

	void init() {
		e = 0; root = _alloc();
		dfnCnt = ans =  0;
	}
	void insert(char *ch) {
			DD *p = root;
			for  (int i = 0, d; ch[i]; i++) {
				d = ch[i] - 'a';
				if (p->x[d] == NULL) p->x[d] = _alloc();
				p = p->x[d];
			}
			p->num++;
	}
	void fail_pointer() {
		root->fail = root;
		int s = 0, t = 0;
		DD *p;
		for (int i = 0; i < CH; ++i) {
			if (root->x[i]) {
				root->x[i]->fail = root;
				root->x[i]->num |= root->num;
				que[t++] = root->x[i];
			} else root->x[i] = root;
		}
		while (s < t) {
			p = que[s++];
			for (int i = 0; i < CH; ++i) {
				if (p->x[i]) {
					p->x[i]->fail = p->fail->x[i];
					p->x[i]->num |= p->fail->x[i]->num;
					que[t++] = p->x[i];

				} else p->x[i] = p->fail->x[i];
			}
		}
	}

	void dfs(DD *rt) {
		rt->useful = true;
		for (int i = 0; i < CH; ++i) {
			if (rt->x[i]->num) continue;
			if (rt->x[i]->useful) continue;
			dfs(rt->x[i]);
		}
	}

	void tar(DD *rt) {
		rt->visited = true;
		rt->dfn = rt->low = ++dfnCnt;
		rt->inq = true;
		int tmp = 0;
		for (int i = 0; i < CH; ++i) {
			if (rt->x[i]->useful == false) continue;
			if (!rt->x[i]->visited) {
				tar(rt->x[i]);
				rt->low = min(rt->low, rt->x[i]->low);
			} else if (rt->x[i]->inq) {
				rt->low = min(rt->low, rt->x[i]->dfn);
			}
			if (rt->x[i]->low <= rt->dfn) {
				tmp++;
			}
		}
		if (tmp > 1) ans = true;
		rt->inq = false;
	}




}acm;

char s[10000];
char ch[2222];




int main() {

	freopen("in.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		acm.init();
		scanf("%d%d", &n, &CH);
		for (int i = 0; i < n; ++i) {
			scanf("%s", ch);
			acm.insert(ch);
		}
		acm.fail_pointer();
		acm.dfs(acm.root);
		acm.tar(acm.root);
		if (acm.ans) {
			puts("Yes");
		} else puts("No");

	}
	return 0;
}

