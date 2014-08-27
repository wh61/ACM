#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>

using namespace std;



char s[44][44];

bool visited[44][44], inq[44][44];


int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool used[44][44];

const int inf = 1000000000;

int main() {

	freopen("in.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf("%s", s[i]);
		}
		int ans = inf;

		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) used[i][j] = false;

		for (int i_ = 0; i_ < n; ++i_) {
			for (int j_ = 0; j_ < m; ++j_) {

				if (used[i_][j_]) continue;

				queue<pair<int, int> > Q;

				Q.push(make_pair(i_, j_));

				int visitedNum = 0;

				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < m; ++j) {
						visited[i][j] = false;
						inq[i][j] = false;
					}
				}

				int nowAns = 0;


				while (true) {
					nowAns++;
					queue<pair<int, int> > q = Q;
					while (!Q.empty()) {
						int x= Q.front().first;
						int y = Q.front().second;
						visited[x][y] = true;
						inq[x][y] = true;
						Q.pop();
					}
					while (!q.empty()) {
						int x = q.front().first, y = q.front().second;
						q.pop();
						if (nowAns == 1) used[x][y] = true;
						visitedNum++;
						for (int i = 0; i < 4; ++i) {
							int vx = x + dx[i], vy = y + dy[i];
							if (vx < 0 || vx >= n || vy < 0 || vy >= m) continue;
							if (visited[vx][vy]) continue;
							if (inq[vx][vy]) continue;
							if (s[vx][vy] == s[x][y]) {
								q.push(make_pair(vx, vy));
								inq[vx][vy] = true;
								visited[vx][vy] = true;
							} else {
								Q.push(make_pair(vx, vy));
								inq[vx][vy] = true;
							}
						}
					}
					if (visitedNum >= n * m) break;
				}
				ans = min(ans, nowAns - 1);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
