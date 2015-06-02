#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;


const int maxn = 1010;
short A[maxn][maxn];
int fa[maxn * maxn];

int dx[] = {0, 1, 0, -1}; 
int dy[] = {1, 0, -1, 0}; 

int getFa(int x) {
	return fa[x] == x ? x : fa[x] = getFa(fa[x]);
}

int main() {
	freopen("1002.in", "r", stdin);
	int T, ca = 0;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		int cnt[105];
		memset(cnt, 0, sizeof(cnt));
		
		vector<vector<short> > vec_x1(105, vector<short>());
		vector<vector<short> > vec_y1(105, vector<short>());
		vector<vector<short> > vec_x2(105, vector<short>());
		vector<vector<short> > vec_y2(105, vector<short>());

		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				int temp;
				scanf("%d", &temp); A[i][j] = temp;
				fa[i * m + j] = i * m + j;
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				for (int k = 0; k < 2; ++k) {
					int x = i, y = j;
					int xx = x + dx[k], yy = y + dy[k];
					if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue; 
					int e = A[x][y] - A[xx][yy];
					if (e < 0) e = -e;
					vec_x1[e].push_back(x);
					vec_y1[e].push_back(y);
					vec_x2[e].push_back(xx);
					vec_y2[e].push_back(yy);
					cnt[e]++;
				}
			}
		}
		int ans = 0;
		for (int e = 0; e <= 100; ++e) {
			for (int i = 0; i < cnt[e]; ++i) {
				int x1 = vec_x1[e][i], y1 = vec_y1[e][i];
				int x2 = vec_x2[e][i], y2 = vec_y2[e][i];
				int index1 = x1 * m + y1;
				int index2 = x2 * m + y2;
				int fa1 = getFa(index1);
				int fa2 = getFa(index2);
				if (fa1 == fa2) continue;
				ans += e;
				fa[fa1] = fa2;
			}
		}
		printf("Case #%d:\n%d\n", ++ca, ans);
	}
	return 0;	
}


