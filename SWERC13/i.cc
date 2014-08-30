#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

char s_[33];

typedef unsigned long long LL;

int cnt[1111];

const LL P = 1007;

inline LL getHash(const string& s) {
	LL tmp = 0;
	int sz = s.size();
	for (int i = 0; i < sz; ++i) {
		tmp = tmp * P + s[i];
	}
	return tmp;
}

int main() {

	freopen("in.txt", "r", stdin);

	int day = 0;
	memset(cnt, 0, sizeof(cnt));
	queue<LL> q;
	map<int, set<LL> > F2S;
	map<LL, string> mp;
	map<LL, int> f;
	while (scanf("%s", s_) != EOF) {

		string str = s_;

		if (str == "<text>") {
			day++;
			while (scanf("%s", s_)) {
				string s = s_;
				if (s == "</text>") break;
				if (s.size() < 4) continue;
				LL val = getHash(s);
				if (mp.find(val) == mp.end()) mp[val] = s;
				q.push(val);
				cnt[day]++;
				int tmp = f[val] = f[val] + 1;
				if (tmp != 0) F2S[tmp - 1].erase(val);
				F2S[tmp].insert(val);
			}
			if (day > 7) {
				int day_ = day - 7;
				for (int i = 0; i < cnt[day_]; ++i) {
					LL val = q.front();
					q.pop();
					int tmp = f[val] = f[val] - 1;
					F2S[tmp + 1].erase(val);
					if (tmp > 0) F2S[tmp].insert(val);
				}
			}

		}

		if (str == "<top") {
			int n;
			scanf("%d %s", &n, s_);
			printf("<top %d>\n", n);
			int m = n;
			for (map<int, set<LL> >::reverse_iterator it = F2S.rbegin(); it != F2S.rend(); ++it) {
				vector<string> v;
				set<LL> &st = it->second;
				for (set<LL>::iterator iter = st.begin(); iter != st.end(); ++iter) {
					v.push_back(mp[*iter]);
				}
				sort(v.begin(), v.end());
				int tot = 0;
				for (int i = 0; i < v.size(); ++i) {
					string &str = v[i];
					int sz = str.size();
					for (int j = 0; j < sz; ++j) {
						printf("%c", str[j]);
					}
					printf(" %d\n", it->first);
					tot++;
				}
				m -= tot;
				if (m <= 0) break;
			}
			puts("</top>");
		}

	}
	return 0;
}
