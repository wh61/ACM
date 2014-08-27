#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>

using namespace std;

const size_t maxn = 333333;

char s_[maxn];


string PreProcess(char* s, int len) {
	string str;
	for (int i = 0; i < len; ++i) {
		if (s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '*') {
			str.push_back(s[i]);
			continue;
		} if (s[i] == '-') {
			if (!(i == 0 || s[i - 1] == '(' || s[i - 1] == '+' || s[i - 1] == '*' || s[i - 1] == '-')) {
				str.push_back(s[i]);
				continue;
			}
		}
		if (s[i] == '-' || (isdigit(s[i]))) {
			int j = i + 1;
			while (j < len && isdigit(s[j])) ++j;
			i = j - 1;
			str.push_back('A');
			continue;
		} else if (isalpha(s[i])) {
			int j = i + 1;
			while (j < len && isalpha(s[j])) ++j;
			i = j - 1;
			str.push_back('A');
			continue;
		}
	}
	return str;
}

struct node {
	int depth;
	node *lc, *rc;
	node *fa, *br;
	int dfn;
	int Leafcnt;
	int Leaf;
	node(int d, node* l, node *r, node *f_):dfn(0), depth(d), Leaf(0), Leafcnt(0), lc(l), rc(r), br(NULL), fa(f_) {}
	node():dfn(0), depth(0), Leaf(0), Leafcnt(0), lc(NULL), rc(NULL), br(NULL), fa(NULL) {}
}pool[maxn];


struct cmp {
	bool operator() (node* a, node* b) {
		if (a->depth == b->depth) {
			if (a->br == NULL || b->br == NULL) return false;

			if (a->br->Leaf == b->br->Leaf) {
				if ((a->br->Leafcnt == 2) == (b->br->Leafcnt == 2)) {
					return a->dfn > b->dfn;
				}
				return (a->br->Leafcnt == 2) < (b->br->Leafcnt == 2);
			}
			return a->br->Leaf < b->br->Leaf;
		}
		return a->depth < b->depth;
	}
};

priority_queue<node*, vector<node*>, cmp> q;

int dfn;

void dfs(node* rt) {
	rt->dfn = ++dfn;
	rt->Leaf = true;
	rt->Leafcnt = 0;
	if (rt->lc != NULL) {
		rt->lc->depth = rt->depth + 1;
		rt->Leaf = false;
		dfs(rt->lc);
		if (rt->lc->Leaf) rt->Leafcnt++;
	}
	if (rt->rc != NULL) {
		rt->rc->depth = rt->depth + 1;
		rt->Leaf = false;
		dfs(rt->rc);
		if (rt->rc->Leaf) rt->Leafcnt++;
	}
	if (rt->Leafcnt == 2)
		q.push(rt);
}



int main() {

	freopen("in.txt", "r", stdin);

	int M;
	while (scanf("%d", &M) != EOF) {
		scanf("%s", s_);
		int len = strlen(s_);
		string s = PreProcess(s_,len);
	//	cout << s << endl;
		len = s.size();
		node *pt2pool = pool;
		stack<node*> val;
		stack<char> op;
		map<char, int> mp;
		mp['('] = 0;
		mp['+'] = mp[')'] = 1;
		mp['-'] = 1;
		mp['*'] = 3;
		s.push_back(')');
		for (int i = 0; i <= len; ++i) {
			if (s[i] == 'A') {
				node *p = new (pt2pool++)node();
				val.push(p);
			} else if (s[i] == '(') {
				op.push(s[i]);
			} else {
				if (s[i] == '+' || s[i] == '-'|| s[i] == '*' || s[i] == ')') {
					while (!op.empty()) {
						char tmp = op.top();
						if (mp[s[i]] <= mp[tmp]) {
							op.pop();
							node *rhs = val.top();
							val.pop();
							node *lhs = val.top();
							val.pop();
							node *p = new (pt2pool++)node(0, lhs, rhs, NULL);
							rhs->fa = p;
							lhs->fa = p;
							rhs->br = lhs;
							lhs->br = rhs;
							val.push(p);
						} else break;
					}
					if (s[i] == ')') {
						if (i != len) op.pop();
					} else op.push(s[i]);
				}
			}
		}

		node* root = val.top();

		root->depth = 0;

		dfn = 0;
		dfs(root);

		int ans = 0;

		while (true) {
			if (q.empty()) break;
			ans++;
			int ti = min((int)q.size(), M);
			for (int i = 0; i < ti; ++i) {
				node* p = q.top();
				q.pop();
				p->lc = NULL;
				p->rc = NULL;
				p->Leaf = true;
				if (p->fa != NULL) {
					++p->fa->Leafcnt;
					if ((p->fa->Leafcnt) == 2) {
						q.push(p->fa);
					}
				}
			}
		}

		while (!q.empty()) q.pop();

		printf("%d\n", ans);


	}
}

