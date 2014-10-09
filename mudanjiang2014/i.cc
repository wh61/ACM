#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef unsigned long long LL;

const int maxn = 111111;


LL mhs[maxn];
char s[8][maxn];
char c[maxn];

const LL P = 10007;
LL p[maxn];
LL shs[8][maxn];
LL sval[8];

char str[maxn];


int dp[maxn][8];
int nx_pos[maxn][8];
int nx_type[maxn][8];

int suf[maxn][8];

int bg[maxn];
int d[maxn];

bool ok[maxn][8];


LL getHash(LL *hs, int l, int r) {
	return hs[r + 1] - hs[l] * p[r - l + 1];
}

int main() {
	int T;
	scanf("%d", &T);
	p[0] = 1;
	for (int i = 1; i < maxn; ++i) p[i] = p[i - 1] * P;
	while (T--) {

		int n, m;

		scanf("%d%d", &n, &m);

		for (int i = 0; i < 4; ++i)	{
			scanf("%s", s[i]);

			bg[i] = i * n + 1;
			d[i] = 1;

			for (int j = 0; j < n; ++j) {
				s[7 - i][j] = s[i][n - j - 1];
			}

			bg[7 - i] = i * n + n;
			d[i] = -1;

		}

		scanf("%s", str);

		for (int i = 0; i < 8; ++i) {
			LL val = 0;
			for (int j = 0; j < n; ++j) val = val * P + s[i][j];
			shs[i][0] = 0;
			for (int j = 0; j < n; ++j) {
				shs[i][j + 1] = shs[i][j] * P + s[i][j];
			}
			sval[i] =  val;
		}

		mhs[0] = 0;
		for (int i = 0; i < m; ++i) mhs[i + 1] = mhs[i] * P + str[i];


		memset(ok, 0, sizeof(ok));
		for (int k = 0; k < 8; ++k) {
			for (int i = 0; i < m; ++i) {
				if (i + n < m) {
					LL tmp = getHash(mhs, i, i + n - 1);
					if (tmp == sval[k]) {
						ok[i][k] = true;
					}
				}
			}
		}

		memset(dp, 0, sizeof(dp));
		memset(suf, 0, sizeof(suf));

		for (int k = 0; k < 8; ++k) {
			for (int i = 0; i < m; ++i) {
				if (i + n < m - 1) continue;
				LL hsVal1 = getHash(mhs, i, m - 1);
				LL hsVal2 = getHash(shs[k], 0, m - i - 1);
				if (hsVal1 == hsVal2) {
					suf[i][k] = true;
				}
			}
		}

		for (int k = 0; k < 8; ++k) {
			dp[0][k] = true;
		}

		for (int k = 0; k < 8; ++k) {
			for (int i = 0; i < m; ++i) {
				if (i < n) {
					LL val1 = getHash(mhs, 0, i);
					LL val2 = getHash(shs[k], n - i - 1 ,n - 1);
					if (val1 == val2) {
						dp[i + 1][k] = true;
						nx_pos[i + 1][k] = 0;
						nx_pos[i + 1][k] = 0;
					}
				} else {
					int r = i + 1, l = i - n;
					if (!ok[i][k]) continue;
					for (int j = 0; j < 8; ++j) if (k + j != 7) {
						if (dp[l][j] == true) {
							nx_pos[r][k] = l;
							nx_type[r][k] = j;
						}
					}
				}
			}
		}


		int ans = 0;

		int suf_pos = -1, suf_type = -1;

		for (int k = 0; k < 8; ++k) {
			if (suf[0][k] == true) {
				suf_pos = 0;
				suf_type = k;
				ans = true;
			}
		}

		if (ans) {
			int ind = bg[suf_type];
			for (int i = 0; i < m; ++i) {
				if (i) printf(" ");
				printf("%d", ind);
				ind += d[suf_type];
			}
			continue;
		}

		for (int k = 0; k < 8; ++k) suf[m][k] = true;

		int pre_pos = -1, pre_type = -1;

		for (int k = 0; k < m; ++k) {
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) if (i + j != 8) {
					if (dp[k + 1][i] && suf[k][j]) {
						pre_pos = k + 1;
						pre_type = i;
						suf_pos = k;
						suf_pos = j;
						ans = true;
					}
				}
			}
		}



		if (ans) {
			stack<M
			while (pre_pos != 0) {
				int tmp_pos = pre_pos, tmp_type = pre_type;
				pre_pos = nx[tmp_pos][tmp_type];
				pre_type = nx[tpm_pos][tmp_type];
				vector<int> v;
				int ind = bg[tmp_type];
				int di = d[tmp_type];
				for (int i = pre_pos; i < tmp_pos; ++i) {
					v.push_back(ind);
					ind += di;
				}
				reverse(v.begin(), v.end());
			}

		}




	}
	return 0;


}
