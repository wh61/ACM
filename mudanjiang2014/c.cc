#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>

using namespace std;

const int maxn = 111111;

int st[maxn], nx[maxn * 4], ve[maxn * 4];
bool visited[maxn];
int tot;

inline void add(int i, int a, int b) {
	ve[i] = b;
	nx[i] = st[a];
	st[a] = i;
}

int checkPoint[maxn];
int ok[maxn];
int cnt;

bool bfs(int s, int nxVe) {
	queue<int> q;
	ok[s] = false;
	ok[nxVe] = false;
	if (!visited[s]) return false;
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = st[v]; i; i = nx[i]) {
			if (visited[ve[i]]) continue;
			if (ok[ve[i]]) {
				visited[ve[i]] = true;
				continue;
			}
			visited[ve[i]] = true;
			q.push(ve[i]);
		}
	}
	return visited[nxVe];
}

int a[maxn];


int main() {

	freopen("in.txt", "r", stdin);

	int T, ca = 0;
	scanf("%d", &T);
	while (T--) {
		int n, m, K;
		scanf("%d%d%d", &n, &m, &K);
		for (int i = 0; i <= n; ++i) st[i] = visited[i] = ok[i] = 0;
		for (int i = 1; i <= K; ++i) {
			scanf("%d", checkPoint + i);
			ok[checkPoint[i]] = true;
		}
		tot = 0;
		for (int i = 0; i < m; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			add(++tot, x, y);
			add(++tot, y, x);
		}

		int L;
		scanf("%d", &L);
		for (int i = 0; i < L; ++i) scanf("%d", a + i);
		int cnt = 0;
		int ans = true;
		for (int i = 0; i < L; ++i) {
			int v1 = a[i];
			int v2 = a[min(i + 1, L - 1)];
			if (!bfs(v1, v2)) {
				ans = false;
			}
		}
		for (int i = 1; i <= n; ++i) if (!visited[i]) ans = false;
		if (ans) puts("Yes"); else puts("No");
	}
	return 0;

}
