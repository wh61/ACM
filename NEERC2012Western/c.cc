#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>


using namespace std;

const int maxn = 111111;

char s_[maxn];
int ans[maxn];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};


int main() {
	freopen("blot.in", "r", stdin);
	freopen("blot.out", "w", stdout);
//	freopen("in.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);

	vector<vector<int> > mp;
	vector<vector<int> > visited;

	for (int i = 0; i < n; ++i) {
		vector<int> vec;
		vector<int> v;
		scanf("%s", &s_);
		for (int j = 0; j < m; ++j) {
			int tmp = s_[j] == '1' ? 1 : 0;
			vec.push_back(tmp);
			v.push_back(0);
		}
		mp.push_back(vec);
		visited.push_back(v);
	}
	int cnt = 0;
	for (int i = 0 ; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (visited[i][j] > 0) {
				continue;
			}
			if (mp[i][j] == 0) continue;
			++cnt;
			queue<pair<int, int> > q;
			q.push(make_pair(i, j));
			visited[i][j] = cnt;
			while (!q.empty()) {
				pair<int, int> pr = q.front();
				q.pop();
				int vx = pr.first, vy = pr.second;
				for (int i = 0; i < 4; ++i) {
					int x = vx + dx[i], y = vy + dy[i];
					if (x < 0 || x >= n || y < 0 || y >= m) continue;
					if (mp[x][y] == 0) continue;
					if (visited[x][y] > 0) continue;
					q.push(make_pair(x, y));
					visited[x][y] = cnt;
				}
			}

		}
	}
	for (int i = 1; i <= cnt; ++i) ans[i] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (mp[i][j] == 0) continue;
			ans[visited[i][j]]++;
		}
	}
	int ans_ = 0;
	for (int i = 1; i <= cnt; ++i) ans_ = max(ans_, ans[i]);
	printf("%d %d\n", cnt, ans_);





	return 0;
}
