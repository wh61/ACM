
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>


using namespace std;

int de[55];
int n;


struct matrix {
	matrix() {
		memset(c, 0, sizeof(c));
		for (int i = 0; i < n; ++i) c[i][i] = 1;
	}
	matrix(const matrix &rhs) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) c[i][j] = rhs.c[i][j];
		}
	}
	double c[55][55];
	friend matrix operator*(const matrix& lhs, const matrix& rhs) ;
};


matrix operator*(const matrix& lhs, const matrix& rhs) {
	matrix rs;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) rs.c[i][j] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k)
				rs.c[i][j] += lhs.c[i][k] * rhs.c[k][j];
		}
	}
	return rs;
}


matrix ksm(const matrix& mx, int step) {
	if (step == 1) {
		return mx;
	}
	matrix a = ksm(mx, step / 2);
	if (step & 1) {
		return mx * a * a;
	} else {
		return a * a;
	}

}

int x[5555], y[5555];



int main() {

	freopen("in.txt", "r", stdin);


	int T;
	scanf("%d", &T);
	while (T--) {
		int m, d;
		scanf("%d%d%d", &n, &m, &d);
		memset(de, 0, sizeof(de));
		int tot = 0;
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", x + i, y + i);
			x[i]--;
			y[i]--;
			de[x[i]]++;
			de[y[i]]++;
		}
		matrix mx;
		for (int i = 0; i < n; ++i) mx.c[i][i] = 0;
		for (int i = 0; i < m; ++i) mx.c[x[i]][y[i]] = 1.0 / de[y[i]], mx.c[y[i]][x[i]] = 1.0 / de[x[i]];

		double ans[55];

		for (int k = 0; k < n; ++k) {
			matrix K(mx);
			for (int i = 0; i < n; ++i) K.c[k][i] = 0;
			for (int i = 0; i < n; ++i) K.c[i][k] = 0;
			matrix rs = ksm(K, d);
			double val[55];
			memset(val, 0, sizeof(val));
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					val[i] += rs.c[i][j] * 1.0 / n;
				}
			}
			ans[k + 1] = 0;
			for (int i = 0; i < n; ++i) ans[k + 1] += val[i];
		}





		for (int v = 1; v <= n; ++v) {
			printf("%.10lf\n", ans[v]);
		}


	}
	return 0;
}
