#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 111;

double mat[MAXN][MAXN + 1], answer[MAXN];
const double eps = 1e-10;

struct op {
	int type;
	int r1, r2;
	double r;
	op(int tp, int r1_, int r2_, double r_):type(tp), r1(r1_), r2(r2_), r(r_) {}
};

// 迒回矩阵的秩

double  matrix[MAXN][MAXN + 1], ans[MAXN];

int gauss(int n, int m, vector<op> &v) {
	int k, t;
	for (k = 0, t = 0; k < m && t < n; ++k, ++t) {
	// k for column; t for row
		int dec = t;
		for (int i = t + 1; i < n; ++i)
		if (fabs(mat[i][k]) > fabs(mat[dec][k]))
			dec = i;
		if (fabs(mat[dec][k]) < eps) {
			--t;
			continue;
		}
		if (dec != t) {
			for (int j = k; j <= m; ++j)
			swap(mat[t][j], mat[dec][j]);
			v.push_back(op(0, t, dec, 0));
		}
		for (int i = t + 1; i < n; ++i) {
			double r = mat[i][k] / mat[t][k];
			mat[i][k] = 0.0;
			for (int j = k + 1; j <= m; ++j)
				mat[i][j] -= mat[t][j] * r;
			v.push_back(op(1, t, i, r));
		}
	}
	for (int i = t; i < n; ++i)
	if (fabs(mat[i][m]) > eps)
		return -1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= m; ++j) {
			matrix[i][j] = mat[i][j];
		}
	}


	if (t == m) for (int k = m - 1; k >= 0; --k) {
		answer[k] = mat[k][m];
		for (int i = k + 1; i < m; ++i)
		answer[k] -= mat[k][i] * answer[i];
		answer[k] /= mat[k][k];
	}
	return t;
}


int c[111][111];
int cnt[MAXN];



int main() {

	freopen("in.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		memset(cnt, 0 ,sizeof(cnt));
		memset(c, 0, sizeof(c));
		for (int i = 0; i < m; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			c[x][y] = 1;
			cnt[x]++;
		}
		memset(mat, 0, sizeof(mat));
		memset(answer, 0, sizeof(answer));
		for (int i = 0; i < n; ++i) {
			mat[i][i] -= 1;
			for (int j = 0; j < n; ++j) if (c[j][i]) {
				mat[i][j] += 1.0 / (double)cnt[j];
			}
		}
		for (int i = 0; i <= n; ++i) mat[n][i] = 1;

		vector<op> o;
		int val = gauss(n + 1, n, o);
		if (val == -1 || val != n) {
			puts("INF");
			continue;
		}

		double oVal = answer[n - 1];

		int da = -1;

		double w[MAXN];

		for (int k = 0; k < n - 1; ++k) {
			if (c[n - 1][k] != 1) {
				memset(w, 0, sizeof(w));
				for (int i = 0; i < n - 1; ++i) if (c[n - 1][i] == 1 || i == k) {
					w[i] = 1.0 / (double)(cnt[n - 1] + 1);
				}
				w[n - 1] = -1;
				w[n] = 1;
				for (int i = 0; i < o.size(); ++i) {
					op &p = o[i];
					if (p.type == 0) {
						int i_ = p.r1, j_ = p.r2;
						swap(w[i_], w[j_]);
					} else {
						int i_ = p.r1, j_ = p.r2;
						w[j_] -= w[i_] * p.r;
					}
				}

				if (fabs(w[n - 1]) < eps) continue;
				if (fabs(w[n]) > eps) continue;

				for (int i = 0; i <= n; ++i) {
					matrix[i][n - 1] = w[i];
				}
				for (int i = n - 1; i >= 0; --i) {
					answer[i] = matrix[i][n];
					for (int j = i + 1; j < n; ++j)
						answer[i] -= matrix[i][j] * answer[j];
					answer[i] /= matrix[i][i];
				}

				double Nval = answer[n - 1];
				if (Nval > oVal + eps) {
					da = k;
					oVal = Nval;
				}
			}
		}
		printf("1 %d\n", da);
	}
	return 0;
}
