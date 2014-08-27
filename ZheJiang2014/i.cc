#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>



using namespace std;

int CH;

struct DD {
	int num;
	DD *fail, *x[26];
	vector<DD*> re;
	bool visited, rvisited;
	void init() {
		num = 0;
		visited = rvisited = 0;
		re.clear();
		memset(x, NULL, sizeof(x));
	}
}dd[120000], *que[120000];

struct ACAutoM {
	int e;
	DD *root;
	DD *_alloc() {dd[e].init(); return &dd[e++];}
	void init() {
		e = 0; root = _alloc();
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
		rt->visited = true;
		for (int i = 0; i < CH; ++i) {
			if (rt->x[i]->num) continue;
			if (rt->x[i]->visited) continue;
			dfs(rt->x[i]);
		}
	}

	void reBuildEdge() {
		for (int i = 0; i < e; ++i) {
			DD *p = dd + i;
			if (!p->visited) continue;
			for (int j = 0; j < CH; ++j) {
				if (p->x[j]->visited == false) continue;
				p->x[j]->re.push_back(p);
			}
		}
	}


	void redfs(DD *rt) {
		rt->rvisited = true;
		int sz = rt->re.size();
		for (int i = 0; i < sz; ++i) {
			DD *ve = rt->re[i];
			if (ve->rvisited) continue;
			redfs(ve);
		}
	}

	bool check() {
		for (int i = 0; i < e; ++i) {
			DD *p = dd + i;
			if (!p->visited) continue;
			int ans = 0;
			for (int j = 0; j < CH; ++j) {
				if (p->x[j]->rvisited) ans++;
			}
			if (ans >= 2) return true;
		}
		return false;
	}

	void del() {
		for (int i = 0; i < e; ++i) dd[i].init();
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
		acm.reBuildEdge();
		acm.redfs(acm.root);
		if (acm.check()) {
			puts("Yes");
		} else {
			puts("No");
		}
		acm.del();
	}
	return 0;
}
