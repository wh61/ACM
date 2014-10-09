#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int n, l[8];
typedef long long LL;

int a[8];
int m;

void dfs(int n, int x, const vector<int> &vec, vector<int> &num) {
	if (x == n) {
		int tmp = 0;
		for (int i = n - 1; i >= 0; --i) {
			tmp = tmp * 10 + a[i];
		}
		num.push_back(tmp);
		return;
	}
	int last;
	if (x == 0) last = 0; else last = a[x - 1];
	for (int i = max(last, vec[x] + 1); i <= m; ++i) {
		a[x] = i;
		dfs(n, x + 1, vec, num);
	}
}



int main() {

	freopen("in.txt", "r", stdin);


	map<int, vector<int> > used;

	int n;
	while (cin >> n) {
		for (int i = 1; i <= n; ++i) {
			cin >> l[i];
		}
		cin >> m;
		map<int, LL> mp[8];
		mp[0][0] = 1;
		typedef map<int, LL>::iterator mapIter;
		for (int k = 1; k <= n; ++k) {
			map<int, LL> &f = mp[k - 1];
			map<int, LL> &g = mp[k];
			for (mapIter it = f.begin(); it != f.end(); ++it) {
				int s = it->first;

				int val = m * 100000000 + l[k] * 10000000 + s;

				map<int, vector<int> >::iterator iter = used.find(val);
				if (iter != used.end()) {
					vector<int> &num = iter->second;
					int sz = num.size();
					for (int i = 0; i < sz; ++i) {
						g[num[i]] += it->second;
					}
					continue;
				}

				vector<int> vec;
				for (int i = 0; i < l[k]; ++i) {
					vec.push_back(s % 10);
					s /= 10;
				}
				vector<int> num;
				dfs(l[k], 0, vec, num);
				int sz = num.size();
				for (int i = 0; i < sz; ++i) {
					g[num[i]] += it->second;
				}
				used[val] = num;
			}
		}
		LL ans = 0;
		map<int, LL> &f = mp[n];
		for (mapIter it = f.begin(); it != f.end(); ++it) {
			ans += it->second;
		}
		cout << ans << endl;
	}
	return 0;
}
