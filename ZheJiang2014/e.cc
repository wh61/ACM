#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

struct node {
	node (char ch_, int id_):ch(ch_), id(id_) {}
	node () {}
	char ch;
	int id;
}a[3000];

int d[3000];
char s[555][555];

int st[3000], nx[1000000], ve[1000000];

int tot;
inline void add(int a, int b) {
	ve[++tot] = b;
	nx[tot] = st[a];
	st[a] = tot;
}

struct cmp {
	bool operator() (int lhs, int rhs) {
		if (a[lhs].ch == a[rhs].ch) {
			return a[lhs].id > a[rhs].id;
		}
		return a[lhs].ch > a[rhs].ch;
	}
};

int Rmp[555];
int Cmp[555];
int cnt = 0;


int main() {

	//freopen("in.txt", "r", stdin);



	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		cnt = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", s[i]);
		}

		memset(Cmp, 0, sizeof(Cmp));
		memset(Rmp, 0, sizeof(Rmp));

		for (int i = 0; i < n; ++i) {
			int ok = false;
			for (int j = 0; j < n; ++j) {
				if (s[i][j] == 'X') ok = true;
			}
			if (!ok) continue;
			a[++cnt] = node('R', i + 1);
			Rmp[i] = cnt;
		}

		for (int j = 0; j < n; ++j) {
			int ok = false;
			for (int i = 0; i < n; ++i) {
				if (s[i][j] == 'O') ok = true;
			}
			if (!ok) continue;
			a[++cnt] = node('C', j + 1);
			Cmp[j] = cnt;
		}


		memset(st, 0, sizeof(st));
		tot = 0;
		memset(d, 0, sizeof(d));

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int r = Rmp[i];
				int c = Cmp[j];
				if (r == 0 || c == 0) continue;
				if (s[i][j] == 'O') {
					add(r, c);
					d[c]++;
				} else {
					add(c, r);
					d[r]++;
				}
			}
		}

		priority_queue<int, vector<int>, cmp> q;

		for (int i = 1; i <= cnt; ++i) {
			if (d[i] == 0) {
				q.push(i);
			}
		}
		int ans = true;
		vector<int> ans_id;
		for (int k = 0; k < cnt; ++k) {
			if (q.empty()) ans = false;
			if (!ans) break;
			int v = q.top();
			ans_id.push_back(v);
			q.pop();
			for (int i = st[v]; i; i = nx[i]) {
				if ((--d[ve[i]]) == 0) {
					q.push(ve[i]);
				}
			}
		}
		if (!ans) {
			puts("No solution");
		} else {
			for (int i = 0; i < cnt; ++i) {
				if (i) printf(" ");
				int ind = ans_id[i];
				printf("%c%d", a[ind].ch, a[ind].id);
			}
			puts("");
		}



	}
	return 0;
}
