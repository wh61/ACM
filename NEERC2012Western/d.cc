#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define CH 26
typedef long long LL;
struct DD {
	LL val;
	DD *x[CH];
	bool mark, num;
	void init() {
		num = 0;
		val = 0;
		mark = false;
		memset(x, NULL, sizeof(x));
	}
}dd[600000];

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
			d = ch[i] - 'a';
			if (p->x[d] == NULL) p->x[d] = _alloc();
			p = p->x[d];
		}
		p->num = true;
	}
}acm;

int dep;

void dfs(DD *p) {
	dep++;
	LL ans = 0;
	for (int i = 0; i < 26; ++i) {
		DD* pc = p->x[i];
		if (pc == NULL) continue;
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
	for (int i = 0; i < 26; ++i) {
		DD* pc = p->x[i];
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
	for (int i = 0; i < 26; ++i) {
		DD* pc = p->x[i];
		if (pc == NULL) continue;
		vec.push_back(i);
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
