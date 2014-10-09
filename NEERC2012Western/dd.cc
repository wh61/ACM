#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <list>

using namespace std;

typedef long long LL;

int nx[2000000];
char c[2000000];
struct DD;
DD *ve[2000000];


struct DD {
	LL val;
	int st;
	bool mark, num;
	void init() {
		num = 0;
		val = 0;
		mark = false;
		st = 0;
	}
}dd[2000000];
int tot;
struct ACAutoM {
	int e;
	DD *root;
	DD *_alloc() {dd[e].init(); return &dd[e++];}
	void init() {
		e = 0; root = _alloc();
	}
	void insert(char *ch) {
		DD *p = root;
		for (int i = 0, d; ch[i]; ++i) {
			d = -1;
			for (int j = p->st; j; j = nx[j]) {
				if (c[j] == ch[i]) {
					d = j;
					break;
				}
			}
			if (d == -1) {
				//p->c.push_back(ch[i]);
				//p->x.push_back(_alloc());
				c[++tot] = ch[i];
				nx[tot] = p->st;
				ve[tot] = _alloc();
				p->st = tot;
				d = tot;
			}
			p = ve[d];
		}
		p->num = true;
	}
}acm;

int dep;

void dfs(DD *p) {
	dep++;
	LL ans = 0;
	for (int i = p->st; i; i = nx[i]) {
		DD* pc = ve[i];
		dfs(pc);
		ans += pc->val;
	}
	LL tmp = 1LL << (40 - dep);

	if (p == acm.root) {
		p->val = ans;
		dep--;
		return;
	}

	if (p->num > 0) {
		p->val = tmp;
		p->mark = true;
	} else {
		if (tmp < ans) {
			p->val = tmp;
			p->mark = true;
		} else {
			p->val = ans;
		}
	}
	dep--;
}


char s[44];


void gao(DD *p, int& cnt) {
	if (p->mark == true) {
		cnt++;
		return;
	}
	for (int i = p->st; i; i = nx[i]) {
		DD* pc = ve[i];
		if (pc == NULL) continue;
		gao(pc, cnt);
	}
}

void dfsGet(DD *p, vector<int> &vec) {
	if (p->mark == true) {
		int sz = vec.size();
		for (int i = 0; i < sz; ++i) {
			printf("%c", 'a' + vec[i]);
		}
		puts("");
		return;
	}
	for (int i = p->st; i; i = nx[i]) {
		DD* pc = ve[i];
		if (pc == NULL) continue;
		vec.push_back(c[i] - 'a');
		dfsGet(pc, vec);
		vec.pop_back();
	}
}

int main() {
//	freopen("in.txt", "r", stdin);
	freopen("compression.in", "r", stdin);
	freopen("compression.out", "w", stdout);
	int n;
	acm.init();
	tot = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", s);
		acm.insert(s);
	}
	dep = -1;
	dfs(acm.root);
	cout << acm.root->val << endl;
	int cnt = 0;
	gao(acm.root, cnt);

	cout << cnt << endl;

	vector<int> vec;
	dfsGet(acm.root, vec);


	return 0;
}
