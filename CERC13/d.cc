#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <queue>

using namespace std;

const size_t maxn = 2322222;

typedef unsigned long long ULL;
typedef long long LL;

int st[maxn], nx[maxn * 3], ve[maxn * 3];
LL re[maxn * 3];
int q[maxn * 8];


inline void add(int i, int a, int b, LL c) {
	ve[i] = b;
	re[i] = c;
	nx[i] = st[a];
	st[a] = i;
}

char s_[2222];

const ULL P = 1007;
const LL MOD = 1000000000;

const LL inf = 1000000000000000000;
LL dist[maxn];
bool inq[maxn];

const int qsz = maxn * 8;

LL spfa(int s, int tt, int n) {
	for (int i = 0; i <= n; ++i) {
		dist[i] = inf;
		inq[i] = false;
	}
	dist[s] = 0;
	inq[s] = true;
//	queue<int> q;
	int head = 1, tail = 1;
	int h = 1, t = 1;
	q[head] = s;
	LL tmp;
	while (head <= tail) {
		int v = q[h];
		head++;
		if (++h >= qsz) h -= qsz;
		inq[v] = false;
		for (int i = st[v]; i; i = nx[i]) {
			tmp = dist[v] + re[i];
			if (tmp < dist[ve[i]]) {
				dist[ve[i]] = tmp;
				if (!inq[ve[i]])
				{
					if (tmp > dist[q[h]]) {
						++tail;
						if (++t >= qsz) t -= qsz;
						q[t] = ve[i];
						inq[ve[i]] = true;

					} else {
						--head;
						if (--h < 0) h += qsz;
						q[h] = ve[i];
						inq[ve[i]] = true;
					}

				}
			}
		}
	}
	return dist[tt];
}



int main() {

	//freopen("in.txt", "r", stdin);


	int T;
	scanf("%d", &T);

	while (T--) {
		int tot = 0;
		map<ULL, int> mp;
		memset(st, 0, sizeof(st));
		scanf("%s", s_);
		int cnt = 0;

		while (scanf("%s", s_) != EOF) {
			int len = strlen(s_);
			if (s_[len - 1] == ',') {
				ULL val = 0;
				for (int i = 0; i < len - 1; ++i) {
					val = val * P + s_[i];
				}
				mp[val] = ++cnt;
			} else {
				ULL val = 0;
				for (int i = 0; i < len; ++i) {
					val = val * P + s_[i];
				}
				mp[val] = ++cnt;
				break;
			}
		}


		scanf("%s", s_);
		int M = 0;
		while (scanf("%s", s_) != EOF) {
			int len = strlen(s_);
			if (s_[len - 1] == ',') {
				M++;
			} else {
				M++;
				break;
			}
		}


		int n = cnt;
		for (int k = 0; k < M; ++k) {
			scanf("%s", s_);
			scanf("%s", s_);
			bool bg = true;
			while (scanf("%s", s_) != EOF) {
				int len = strlen(s_);
				if (s_[len - 1] == ',') {
					ULL val = 0;
					for (int i = 0; i < len - 1; ++i) {
						val = val * P + s_[i];
					}
					int station = mp[val];
					++cnt;
					add(++tot, cnt, station, 0);
					add(++tot, station, cnt, MOD);
					++cnt;
					add(++tot, cnt, station, 0);
					add(++tot, station, cnt, MOD);
					if (!bg) {
						add(++tot, cnt - 3, cnt - 1, -1);
						add(++tot, cnt, cnt - 2, -1);
					} else {
						bg = false;
					}
				} else {
					ULL val = 0;
					for (int i = 0; i < len; ++i) {
						val = val * P + s_[i];
					}
					int station = mp[val];
					++cnt;
					add(++tot, cnt, station, 0);
					add(++tot, station, cnt, MOD);
					++cnt;
					add(++tot, cnt, station, 0);
					add(++tot, station, cnt, MOD);
					if (!bg) {
						add(++tot, cnt - 3, cnt - 1, -1);
						add(++tot, cnt, cnt - 2, -1);
					} else {
						bg = false;
					}
					break;
				}
			}
		}

		string s_str, t_str;

		scanf("%s", s_);
		scanf("%s", s_);
		scanf("%s", s_);
		scanf("%s", s_);



		s_str = s_;

		ULL val;
		int sz;

		val = 0;
		sz = strlen(s_);
		for (int i = 0; i < sz; ++i) {
			val = val * P + s_[i];
		}
		int ss = mp[val];


		scanf("%s", s_);
		scanf("%s", s_);
		scanf("%s", s_);
		scanf("%s", s_);

		t_str = s_;

		val = 0;
		sz = strlen(s_);
		for (int i = 0; i < sz; ++i) {
			val = val * P + s_[i];
		}
		int tt = mp[val];


        n = cnt;

        LL ans = spfa(ss, tt, n);

        LL Line = ans / MOD + 1;
        LL Mi = (Line * MOD - ans);

        if (ans == 0) Line = 0, Mi = 0;

        int line = Line;
        int mi = Mi;

        printf("optimal travel from %s to %s: ", s_str.c_str(), t_str.c_str());

        printf("%d", line);

        if (line == 1) {
			printf(" line, ");
        } else {
			printf(" lines, ");
        }

        printf("%d", mi);

         if (mi == 1) {
			printf(" minute");
        } else {
			printf(" minutes");
        }

        puts("");


	}
	return 0;
}
