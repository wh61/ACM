#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>


using namespace std;


const int maxT = 11111;

int isSubmitPoint[maxT];

int newTime[maxT];
int oldTime[maxT];
int isSub[maxT];

int N, M;

struct problem {
	int id, t, s;
	problem(int t_, int s_, int id_):t(t_), s(s_), id(id_) {}
	problem() {}
};

bool cmp(const problem& a, const problem& b) {
	return a.t < b.t;
}


problem p[33];
int submitPoint[maxT];
int f[maxT][20];
int g[maxT][20];


void getAns(int totalSubmitNum, int& S, int& G) {
	int cnt = totalSubmitNum;
	memset(isSub, 0, sizeof(isSub));
	for (int i = 10000; i >= 0; --i) {
		if (isSubmitPoint[i]) {
			isSub[i] = true;
			cnt--;
		}
		if (cnt == 0) break;
	}
	if (cnt > 0) return;
	cnt = 0;
	int ind = 0;
	for (int i = 1; i <= 10000; ++i) {
		if (!isSub[i]) newTime[++cnt] = i; else submitPoint[++ind] = cnt;
	}
	int n = N / 2, m = N - n;

	// 1~n;
	for (int mask = 0; mask < 1 << n; ++mask) {
		int  numK = 0;
		for (int i = 0; i < n; ++i) if ((mask >> i)& 1) numK++;
		if (numK > totalSubmitNum) continue;
		//check
		int timeFinish = 0;
		int totalS = 0;
		int ind = 0, numK_ = 0;
		for (int i = 0; i < n; ++i) if ((mask >> i) & 1) {
			timeFinish += p[i].t;
			totalS += p[i].s;
			if (timeFinish <= submitPoint[++ind]) numK_++;
		}
		if (numK == numK_) {
			if (totalS > f[timeFinish][numK]) {
				f[timeFinish][numK] = totalS;
				g[timeFinish][numK] = mask;
			}
		}
		//endCheck
	}

	for (int numK = 0; numK <= min(n, totalSubmitNum); numK++) {
		for (int time = 1; time <= 10000; time++) {
			if (f[time - 1][numK] > f[time][numK]) {
				f[time][numK] = f[time - 1][numK];
				g[time][numK] = g[time - 1][numK];
			}
		}
	}

	int maxS = 0, maxG = 0;
	//n + 1 ~ N

	for (int mask = 0; mask < 1 << m; ++mask) {
		int numK = 0;
		for (int i = 0; i < m; ++i) if ((mask >> i) & 1) numK++;
		if (numK > totalSubmitNum) continue;

		int ind = totalSubmitNum + 1;
		int lastOKtime = 10001;
		int totalS = 0;
		for (int i = m - 1; i >= 0; --i) if ((mask >> i) & 1){
			int s = p[i + n].s;
			int t = p[i + n].t;
			totalS += s;
			int t1 = lastOKtime - 1, t2 = submitPoint[--ind];
			lastOKtime = min(t1, t2) - t + 1;
		}
		if (lastOKtime <= 0) continue;
		int S = totalS + f[lastOKtime - 1][totalSubmitNum - numK];
		int GG = g[lastOKtime - 1][totalSubmitNum - numK] | (mask << n);
		if (S > maxS) {
			maxS = S, maxG = GG;
		}
	}
	S = maxS;
	G = maxG;

	for (int i = 0; i <= totalSubmitNum; ++i) {
		for (int j = 0; j <= 10000; ++j) f[i][j] = g[i][j] = 0;
	}

}


int main() {


	while (scanf("%d%d", &N, &M) != EOF) {
		memset(isSubmitPoint, 0, sizeof(isSubmitPoint));

		for (int i = 0; i < N; ++i) {
			int s, t;
			scanf("%d%d", &t, &s);
			p[i] = problem(s, t, i);
		}

		sort(p, p + N, cmp);

		int SubmitPointCnt = 0;
		for (int i = 0; i < M; ++i) {
			int L, R;
			scanf("%d%d", &L, &R);
			for (int j = L + 1; j <= R; ++j) { isSubmitPoint[j] = true; SubmitPointCnt++;}
		}

		int ansS = 0, ansG = 0;
		for (int i = 1; i <= min(N, SubmitPointCnt); ++i) {
			int S = 0, G = 0;
			getAns(i, S, G);
			if (S > ansS) {
				ansS = S;
				ansG = G;
			}
		}

        vector<int> v;
        for (int i = 10000; i >= 0; --i) if (isSubmitPoint[i]) v.push_back(i);
        int ind = 0;
        vector<pair<int,int> > ans;
        for (int i = N - 1; i >= 0; --i) {
			if ((ansG >> i) & 1) {
				ans.push_back(make_pair(p[i].id + 1, v[ind++] - 1));
			}
        }
        int sz = ans.size();
        reverse(ans.begin(), ans.end());
        printf("%d %d\n", ansS, sz);
        for (int i = 0; i < sz; ++i) {
			printf("%d %d\n", ans[i].first, ans[i].second);
        }
	}
	return 0;
}
