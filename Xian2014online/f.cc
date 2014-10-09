#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int g[4][6] = {
{3, 2, 0, 1, 4, 5},
{2, 3, 1, 0, 4, 5},
{5, 4, 2, 3, 0, 1},
{4, 5, 2, 3, 1, 0}
};

const int maxn = 6;

typedef unsigned long long LL;

LL toHash(const vector<int> &v) {
	LL tmp = 0;
	for (int i = 0; i < 6; ++i) {
		tmp = tmp * 1007 + v[i];
	}
	return tmp;
}

inline void change(vector<int> &v, int step) {
	int a[6];
	for (int i = 0; i < 6; ++i) a[i] = v[g[step][i]];
	for (int i = 0; i < 6; ++i) v[i] = a[i];
}

int main() {

	freopen("in.txt", "r", stdin);


	int a[maxn], b[maxn];
	while (cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5]) {
		for (int i = 0; i < 6; ++i) cin >> b[i];
		vector<int> s(b, b + 6);
		queue<vector<int> > q;
		q.push(s);
		map<LL, int> mp;
		mp[toHash(s)] = 0;
		while (!q.empty()) {
			LL val0 = toHash(q.front());
			for (int i = 0; i < 4; ++i) {
				vector<int> v = q.front();
				change(v, i);
				LL val = toHash(v);
				if (mp.find(val) != mp.end()) {
					continue;
				}
				mp[val] = mp[val0] + 1;
				q.push(v);
			}
			q.pop();
		}
		vector<int> target(a, a + 6);
		LL tar = toHash(target);
		if (mp.find(tar) == mp.end()) {
			puts("-1");
		} else {
			printf("%d\n", mp[tar]);
		}
	}
	return 0;
}
