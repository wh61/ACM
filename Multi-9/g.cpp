#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxn 1005
#define maxm 30005
#define inf 0x7fffffff

typedef int type;

struct Edge{
	int iu, iv, ru, rv;
	type val;
	int next;
} E[2][maxn];
int l[2][maxn], e[2];
int ip[maxn], rp[maxn];
int sign[maxn], ID[maxn];
type In[maxn];

void init(bool f = false) {
	memset(l[f], -1, sizeof(l[f]));
	e[f] = 0;
}

inline void _ins(bool f, int iu, int iv, int ru, int rv, type val) {
	E[f][e[f]].iu = iu; E[f][e[f]].iv = iv; E[f][e[f]].ru = ru; E[f][e[f]].rv = rv;
	E[f][e[f]].val = val; E[f][e[f]].next = l[f][iv];
	l[f][iv] = e[f]++;
}

inline void insert(int u, int v, type val) {
	if (u == v) return;
	_ins(false, u, v, u, v, val);
}

bool Directed_MST(int root, int N, type &ret) {
	ret = 0;
	bool f =false;
	while (true) {
		for (int i = 0; i < N; ++i) {
			if (i == root) continue;
			In[i] = inf;
			int ind;
			for (int p = l[f][i]; p >= 0; p = E[f][p].next) {
				if ((E[f][p].val < In[i]) || (
				(E[f][p].val == In[i]) && (E[f][p].rv < E[f][ind].rv))) {
					In[i] = E[f][p].val;
					ind = p;
				}
			}
			if (In[i] < inf) {
				ret += In[i];
				ip[E[f][ind].iv] = E[f][ind].iu;
				rp[E[f][ind].rv] = E[f][ind].ru;
			} else {
				return false;
			}
		}
		memset(sign, -1, sizeof(sign));
		memset(ID, -1, sizeof(ID));
		int cnt = 0;
		for (int i = 0; i < N; ++i) {
			int v = i;
			while (sign[v] == -1 && v != root) {
				sign[v] = i;
				v = ip[v];
			}
			if (sign[v] == i) {
				int u = v;
				do {
					ID[v] = cnt;
					v = ip[v];
				} while (v != u);
				cnt++;
			}
		}
		if (cnt == 0) break;
		for (int i = 0; i < N; ++i) if (ID[i] == -1) ID[i] = cnt++;
		init(!f);
		#define EE (E[f][p])
		for  (int i = 0 ; i < N; ++i) {
			for (int p = l[f][i]; p != -1; p = E[f][p].next) {
				if (ID[EE.iu] != ID[EE.iv]) {
					_ins(!f, ID[EE.iu], ID[EE.iv], EE.ru, EE.rv, EE.val - In[EE.iv]);
				}
			}
		}
		N = cnt;
		root = ID[root];
		f = !f;
	}
	return true;
}




int A[maxn];
int mp[55][555];




int main() {


	freopen("in.txt", "r", stdin);

	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {

		if (n == 0 && m == 0) break;

		for (int i = 1; i <= n; ++i) scanf("%d", A + i);

		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= A[i]; ++j) {
				mp[i][j] = ++cnt;
			}
		}

		int s = 0;

		init();

		for (int i = 1; i <= n; ++i) {
			insert(s, mp[i][0], 0);
			for (int j = A[i]; j > 0; --j) {
				insert(mp[i][j], mp[i][j - 1], 0);
			}
		}

		for (int i = 0; i < m; ++i) {
			int c, l1, d, l2, mm;
			scanf("%d%d%d%d%d", &c, &l1, &d, &l2, &mm);
			insert(mp[c][l1], mp[d][l2], mm);
		}

		int ans = 0;

		if (!Directed_MST(s, cnt + 1, ans)) {
			puts("-1");
		} else printf("%d\n", ans);

	}
	return 0;
}

