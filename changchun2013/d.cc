#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 200002;

typedef long long LL;
typedef long double LD;

int X[maxn], Y[maxn];
int x[maxn * 3];
LD y[maxn * 3];
LD sum[maxn * 3];
int d;

const LD eps = 1e-8;


struct line {
	LD x, y1, y2;
};

inline LD getVal(const line& l1, LD mid) {
	LD tmp1 = ((l1.y2 - l1.y1) * mid / l1.x + l1.y1 + l1.y1) * mid;
	return tmp1 / 2;
}

inline LD getMx(const line& l1, const line& l2) {
	LD tmp1 = (l1.y1 + l1.y2) / 2 * l1.x;
	LD tmp2 = (l2.y1 + l2.y2) / 2 * l2.x;
	LD ans = max(-tmp1 + tmp2, (LD)0.0);
    LD k2 = (l2.y2 - l2.y1) / (l2.x);
    LD k1 = (l1.y2 - l1.y1) / (l1.x);
    LD t = (l2.y1 - l1.y1) / (k1 - k2);
    if (0 <= t && t <= l1.x) {
		LD tmp = -getVal(l1, t) + getVal(l2, t);
		ans = max(ans, tmp);
    }
    return ans;

}


int main() {

	freopen("in.txt", "r", stdin);

	int n, L;
	int T;
	scanf("%d", &T);
	while (scanf("%d%d", &n, &L) != EOF) {
		for (int i = 1; i <= n; ++i) {
			int x_, y_;
			scanf("%d%d", &x_, &y_);
			X[i] = x_;
			Y[i] = y_;
		}
		scanf("%d", &d);
		d *= 2;
	//	map<int, LD> xy;
		vector<pair<int, LD> > v;
		for (int i = 1; i <= n; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (j == 0) continue;
				int tmp = X[i] + d * j;
				if (0 <= tmp && tmp <= L) {
					int id = lower_bound(X + 1, X + n + 1, tmp) - X;
					if (id <= 1) continue;
					int x1 = X[id - 1], y1 = Y[id - 1];
					int x2 = X[id], y2 = Y[id];
					LD yy = (LD)y1 + (LD)(y2 - y1) / (LD)(x2 - x1) * (LD)(tmp - x1);
					v.push_back(make_pair(tmp, yy));
//					xy[tmp] = yy;
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
//			xy[X[i]] = Y[i];
			v.push_back(make_pair(X[i], (LD)Y[i]));
		}

		sort(v.begin(), v.end());

		n = 0;
		for (int i = 0; i < v.size(); ++i) {
			if (i > 0 && v[i].first == v[i - 1].first) continue;
			x[++n] = v[i].first;
			y[n] = v[i].second;
		}
		sum[0] = sum[1] = 0;
		for (int i = 2; i <= n; ++i) {
			sum[i] = sum[i - 1] + (y[i] + y[i - 1]) / 2 * (x[i] - x[i - 1]);
		}

		LD ans = 0;

		if (L == d) ans = sum[n] / d;

		for (int i = 1; i < n; ++i) {
			if (x[i] + d == x[i + 1]) {
				ans = max(ans, (y[i] + y[i + 1]) / 2);
			}
			int i_1 = lower_bound(x + 1, x + n + 1, x[i] - d) - x;
			int i_2 = lower_bound(x + 1, x + n + 1, x[i + 1] - d) - x;
			if (x[i_1] == x[i] - d && x[i_2] == x[i + 1] - d) {
				LD s = sum[i] - sum[i_1];
				line l1, l2;
				l1.x = l2.x = x[i + 1] - x[i];
				l1.y1 = y[i_1];
				l1.y2 = y[i_2];
				l2.y1 = y[i];
				l2.y2 = y[i + 1];

				s += getMx(l1, l2);
				ans = max(ans, s / d);
			} else continue;


		}
		double ans_ = ans;
		printf("%.3lf\n", ans_);
	}
	return 0;
}
