#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

const int maxn = 333333;


int L[maxn];
int R[maxn];
int d[maxn];

int f[maxn];
int nx[maxn];
int tp[maxn];




int main() {

	freopen("in.txt", "r", stdin);

	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", d + i);

		queue<int> q;

		for (int i = 1; i <= n; ++i) L[i] = R[i] = f[i] = nx[i] = tp[i] = 0;

		for (int i = 1; i <= n; ++i) {
			while (!q.empty()) {
				int st = q.front();
				if (i - st <= d[i] - 1) {
					break;
				} else {
					q.pop();
				}
			}
			if (q.empty()) L[i] = 0; else L[i] = i - q.front();
			q.push(i);
		}

		while (!q.empty()) q.pop();
		for (int i = n; i >= 1; --i) {
			while (!q.empty()) {
				int st = q.front();
				if (st - i <= d[i] - 1) {
					break;

				} else {
					q.pop();
				}
			}
			int tmp;
			if (q.empty()) tmp = 0; else tmp = q.front() - i;
			int r = tmp + i;
			if (tmp > R[r]) R[r] = tmp;
			q.push(i);
		}


		int mostLeft = n + 1;
		R[n + 1] = 0;
		for (int i = n; i >= 1; --i) {
			mostLeft = min(i - R[i], i + 1 - R[i + 1]);
			R[i] = max(R[i], i - mostLeft);
		}

		f[0] = 0;

        for (int i = 1; i <= n; ++i) {
			if (L[i] < R[i]) {
				tp[i] = 1;
				f[i] = f[i - R[i] - 1] + 1;
			} else {
				tp[i] = 0;
				f[i] = f[i - L[i] - 1] + 1;
			}
        }


        printf("%d\n", f[n]);
        int val = n;
        vector<pair<int, int > > ans;
        while (val != 0) {
			if (tp[val] == 1) {
				ans.push_back(make_pair(val, val - R[val]));
				val = val - R[val] - 1;
			} else {
				ans.push_back(make_pair(val - L[val], val));
				val = val - L[val] - 1;
			}
        }

        for (int i = 0; i < ans.size(); ++i) {
			printf("%d %d\n", ans[i].first, ans[i].second);
        }

	}
	return 0;
}
