#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

const size_t maxn = 55;

char mp[maxn][maxn];
bool ok[maxn][maxn];
int visited[maxn][maxn];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int n, m;

void dfs(int x, int y) {
	if (visited[x][y]) return;
	visited[x][y] = true;
	for (int i = 0; i < 4; ++i) {
		int x_ = x + dx[i];
		int y_ = y + dy[i];
		if (x_ < 0 || x_ >= n || y_ < 0 || y_ >= m) {
			continue;
		}
		if (ok[x_][y_]) {
			dfs(x_, y_);
		}
	}
}

int main() {

	freopen("in.txt", "r", stdin);


	while (scanf("%d%d", &m, &n) != EOF) {
		for (int i = 0; i < n; ++i) {
			scanf("%s", mp[i]);
		}
		int pos_x, pos_y;
		memset(ok, true, sizeof(ok));
		memset(visited, false, sizeof(visited));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (mp[i][j] == 'P') {
					pos_x = i;
					pos_y = j;
				}
				if (mp[i][j] == '#') {
					ok[i][j] = false;
				}
				if (mp[i][j] == 'T') {
					ok[i][j] = false;
					for (int k = 0; k < 4; ++k) {
						if (i + dx[k] < 0 || i + dx[k] >= n || j + dy[k] < 0 || j + dy[k] >= m) {
							continue;
						}
						ok[i + dx[k]][j + dy[k]] = false;
					}
				}
			}
		}
		int ans = 0;
		if (!ok[pos_x][pos_y]) {
			ans = 0;
		} else {
			dfs(pos_x, pos_y);
			int addMore = 0;
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					if (visited[i][j] && mp[i][j] == 'G') {
						ans++;
					}
					int flag = 0;
					if (!visited[i][j] && mp[i][j] == 'G') {
						for (int k = 0; k < 4; ++k) {
							if (i + dx[k] < 0 || i + dx[k] >= n || j + dy[k] < 0 || j + dy[k] >= m) {
								continue;
							}
							if (visited[i + dx[k]][j + dy[k]]) {
								flag = 1;
							}
						}
						ans += flag;
					}
				}
			}
			ans += addMore;
		}
		printf("%d\n", ans);

	}
	return 0;
}
